# crop.rb
require "rmagick"

["チャーハン", "ピラフ"].each do |word|
	images = Dir.glob("raw/#{word}/*")
	images.each do |image|
		original = Magick::Image.read(image).first
		resized = original.resize_to_fit(480, 320)
		basename = File.basename(image, File.extname(image)) + ".jpg"
		resized.write("resized/#{word}/#{basename}")  #=> 160x120にリサイズされる
	end
end
