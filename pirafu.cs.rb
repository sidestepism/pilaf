require 'google_custom_search_api'

GOOGLE_API_KEY = "AIzaSyBDrob40Q6RASwQuIDux0TSQLN3qI2Tdeg"
GOOGLE_SEARCH_CX = 

start = 1
begin
results = GoogleCustomSearchApi.search("poker",:start => start)
if results.queries.keys.include?("nextPage")
  start = results.queries.nextPage.first.startIndex
else
  start = nil
end
end while start.nil? == false
