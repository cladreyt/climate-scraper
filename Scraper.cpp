#include <iostream>
#include <fstream>
#include "cpr/cpr.h"
#include "gumbo.h"

using namespace std;

string extract_html_page(string url)
{
    cpr::Response response = cpr::Get(cpr::Url{ url });
    if (response.status_code != 200) return url + " not found\n";
    return response.text;
}

string compute(string& page_content, string symbol, int addition) {
    int add = page_content.find(symbol);
    string toReturn = page_content.substr(0, add);
    page_content = page_content.substr(add + addition);
    return toReturn;
}

int main()
{
    string currentCity = "maryland";
    ifstream cityLinks;
    string city;
    cityLinks.open("climateLinks.txt");
    ofstream writeCsv(currentCity + "-stats.csv");
    writeCsv << "city,state,rainfall,snowfall,precipitation,sunny,julHigh,janLow,comfort" << "\n";
    int num = 0;
    while (city.find("/" + currentCity + "/") == -1) {
        getline(cityLinks, city);
        cout << ".";
    }
    cout << endl;
    while(city.find("/" + currentCity + "/") != -1) {
        string page_content = extract_html_page(city); 
        cout << city << endl;

        page_content = page_content.substr(page_content.find("2rem\">Climate in ") + 17);
        int comma = page_content.find(", ");
        string cityName = page_content.substr(0, comma);
        string stateName = page_content.substr(comma+2, page_content.find("<") - cityName.length() - 2);
        cout << cityName << " " << stateName << endl;

        int index = page_content.find("title='The annual rainfall in inches.")+96;
        page_content = page_content.substr(index, 2400);

        string rainfall = compute(page_content, " ", 275);
        string snowfall = compute(page_content, " ", 322);
        string precip = compute(page_content, " ", 310);
        string sunny = compute(page_content, " ", 332);
        string julHigh = compute(page_content, "&", 334);
        string janLow = compute(page_content, "&", 691);
        string comf = page_content.substr(0, page_content.find("<"));

        cout << "\train: " << rainfall << " snow: " << snowfall << " precip: " << precip << endl;
        cout << "\tsunny: " << sunny <<" julHigh: " << julHigh <<" janLow: " << janLow << endl;
        cout << "\tcomf: " << comf << endl;
        writeCsv << cityName << "," << stateName << "," << rainfall << ","
            << snowfall << "," << precip << "," << sunny << "," << julHigh << ","
            << janLow << "," << comf << "\n";
        cout << "[" << num << "] recorded" << endl;
        num++;
        getline(cityLinks, city);
    }
    //http://www.bestplaces.net/find/state.aspx?state=dc - taken out
    // https://www.bestplaces.net/climate/city/alaska/adak - still in there
    // https://www.bestplaces.net/climate/city/arizona/aguila - still in there
    // https://www.bestplaces.net/climate/city/arkansas/adona - still in there
    // https://www.bestplaces.net/climate/city/california/acalanes_ridge - still in there
    //https://www.bestplaces.net/climate/city/california/piñon_hills - taken out
    writeCsv.close();
    cityLinks.close();
}