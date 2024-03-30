#include <iostream>
#include <string>
#include "../curl/curl.h"
#include "../rapidjson/document.h"


using namespace std;
using namespace rapidjson;

const string API_Key = "5ba9593f80c849a0b3403917242603"; // Declaring API Key as a constant

size_t write_callback(char *ptr, size_t size, size_t nmemb, string *data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

string HTTPRequest(const string &url)
{
    string response_data;

    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if (curl)
    {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to receive data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Pass the response data pointer to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            cerr << "Failed to send HTTP request: " << curl_easy_strerror(res) << endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    else
    {
        // Error in initialization of libcurl
        cerr << "Failed to initialize libcurl." << endl;
    }

    return response_data;
}

void WeatherData(const string &httprequest)
{
    Document doc;
    doc.Parse(httprequest.c_str());

    if (doc.HasParseError())
    {
        cerr << "Error parsing JSON data: " << doc.GetParseError() << endl;
        return;
    }

    const Value &location = doc["location"];
    float coord_lon = location["lon"].GetFloat();
    float coord_lat = location["lat"].GetFloat();
    string timezone = location["tz_id"].GetString();

    const Value &current = doc["current"];
    float currentTemp = current["temp_c"].GetFloat();
    float humidity = current["humidity"].GetFloat();
    const Value &condition = current["condition"];
    string weatherDescription = condition["text"].GetString();

    const Value &forecastday = doc["forecast"]["forecastday"][0];
    const Value &day = forecastday["day"];
    float minTemp = day["mintemp_c"].GetFloat();
    float maxTemp = day["maxtemp_c"].GetFloat();

    // Display weather information
    cout << "Coordinates - Latitude: " << coord_lat << endl;
    cout << "Coordinates - Longitude: " << coord_lon << endl;
    cout << "Weather Description: " << weatherDescription << endl;
    cout << "Current Temperature: " << currentTemp << "°C" << endl;
    cout << "Minimum Temperature: " << minTemp << "°C" << endl;
    cout << "Maximum Temperature: " << maxTemp << "°C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Timezone: " << timezone << endl;
}

int main()
{

    string location; // Declaring variables
    string response;

    cout << "Please enter location: " << endl;
    getline(cin, location); // Taking user input

    string url = "http://api.weatherapi.com/v1/forecast.json?key=" + API_Key + "&q=" + location + "&days=1&aqi=no&alerts=no"; // URL for HTTP GET Request

    response = HTTPRequest(url); // Calling function for HTTP GET Request
    WeatherData(response);       // Calling function to parse the recieved JSON data

    return 0;
}