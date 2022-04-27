# climateScraper
scraping for climate stats in certain areas of USA states, to compile overall stats file and info.
Code is in C++, mostly just a fun side project.

This project initially started just because I was interested to see if I could find my ideal climate within the US.
There's no easy to find online tool that can tell you compatible areas for you to live based on very specific weather 
preferences. So this project is to compile climate stats in all areas of the US, and make them comprehensive and searchable.

First, I had to get the links to all the specific areas that I wanted to scrape (this would be every listed area in the US).
I did this by first scraping all of the state links in state_links.txt file, and from there I scraped each of these for city links.
I essentially searched for each href link and found that the city links had a certain format to them. I recorded each link that fit 
this format in the climateLinks.txt file. The code uploaded here goes through all of those links and records info from those addresses.

Info collected is average rainfall, snowfall, days of precipitation, sunny days, july high, january low, and total comfort index
(this is determined from bestplaces.com's algorithm, but I'm just taking the publicly published values).
