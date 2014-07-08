var acctKey = 'ap8ETTkawv/QMNzqt92kx/jElr/L0SC1r4h9SESU6rs';
var rootUri = 'https://api.datamarket.azure.com/Bing/Search';
var auth = new Buffer([acctKey, acctKey].join(':')).toString('base64');
var path = require('path');
var async = require('async');
var https = require('https');
var request = require('request').defaults({
    headers: {
        'Authorization': 'Basic ' + auth
    }
});
var http = require('http');
var fs = require('fs');

var i = 0;

function range(len) {
    return Array.apply(null, {
        length: len
    }).map(Number.call, Number)
}

function download(key, url, cb) {
    try {
        console.log("downloading", i++, url)
        var basename = path.basename(url).replace(/\?.+$/g, '');
        if (basename == '') basename = 'image'
        if (basename.length > 64) basename = basename.substring(0, 64)
        var file = fs.createWriteStream("bing/" + key + "/" + basename);
        request(url).on("end", cb).on("error", cb).pipe(file);
    } catch (e) {
        console.log("donwload err:", e);

    }
}

// here's how to perform a query:
var service_op = "/v1/Composite";



async.eachSeries(process.argv.splice(0, 2), function(query, cb) {
    async.eachSeries(range(20), function(i, cb) {
        console.log("page", i);

        try {
            request.get({
                url: rootUri + '/' + service_op,
                qs: {
                    $format: 'json',
                    Query: "'" + query + "'",
                    Sources: "'image'",
                    ImageFilters: "'Style:Photo'",
                    $Skip: i * 100
                }
            }, function(err, response, body) {
                if (err) {
                    console.log(err.message);
                    cb();
                } else if (response.statusCode !== 200) {
                    console.log(response.body);
                    cb();
                } else {
                    var results = JSON.parse(response.body);
                    async.eachLimit(results.d.results[0].Image, 10, function(Image, cb) {
                        download(query, Image.MediaUrl, cb);
                    }, function(err) {
                        console.log("download each ended");
                        if (err) console.log("err", err);
                        cb();
                    })
                }
            });
        } catch (e) {
            console.log("api request err", e);
        }
    }, function(err) {
        if (err) console.log("err", err);
        cb();
    });
}, function(err) {
    if (err) console.log("err", err);
});