
require 'google_custom_search_api'


["チャーハン", "ピラフ"].each do |word|
	p word
	offset = 32
	i = offset

	search = Google::Search::Image.new(:query => word, :api_key => "AIzaSyBDrob40Q6RASwQuIDux0TSQLN3qI2Tdeg", :offset => offset)
	search.each do |image|
		i += 1
		name = URI.parse(File.basename(image.uri)).path
		print "#{i}: #{image.uri}\n"
		ext = File.extname(name)
		file = open("raw/#{word}/#{i}#{ext}", "w")
		file << open(image.uri).read
		file.close()
	end

end




