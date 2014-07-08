# crop.rb
require "rmagick"

["チャーハン", "ピラフ", "能年玲奈"].each do |word|		
	images = Dir.glob("bing/#{word}/*")
	images.each do |image|
		begin
			original = Magick::Image.read(image).first
			resized = original.resize_to_fill(480, 320)
			basename = File.basename(image, File.extname(image)) + ".jpg"
			resized.write("resized-bing/#{word}/#{basename}")  #=> 160x120にリサイズされる
		rescue Exception

		end
	end
end
