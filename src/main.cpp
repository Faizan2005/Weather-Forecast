#include <iostream>
#include <string>
#include "../curl/curl.h"
#include "../rapidjson/document.h"

using namespace std;
using namespace rapidjson;

const string API_Key = "5ba9593f80c849a0b3403917242603"; // Declaring API Key as a constant

// ANSI escape codes for colors
const string cyan = "\033[1;36m";
const string yellow = "\033[1;33m";
const string green = "\033[1;32m";
const string red = "\033[1;31m";
const string reset = "\033[0m";
const string orange = "\033[38;5;208m";
const string blue = "\033[38;5;27m";  

// Callback function to receive data from HTTP request
size_t write_callback(char *ptr, size_t size, size_t nmemb, string *data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

// Function to make HTTP request
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
            cerr << red << "Failed to send HTTP request: " << curl_easy_strerror(res) << reset << endl;
        }

        // Check if JSON data is parsable or not (used to determine if location/coordinates entered are correct or not)
        Document doc;
        if (!doc.Parse(response_data.c_str()).HasMember("location"))
        {
            return string("Invalid location/coordinates - please try again.");
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    else
    {
        // Error in initialization of libcurl
        cerr << red << "Failed to initialize libcurl." << reset << endl;
    }
    return response_data;
}

// Function to parse JSON data and display weather data
void WeatherData(const string &httprequest)
{
    int i;
    Document doc;
    doc.Parse(httprequest.c_str());

    if (doc.HasParseError()) // Checking parsing error
    {
        cerr << red << "Error parsing JSON data: " << doc.GetParseError() << reset << endl;
        return;
    }

    // Get location and weather data
    const Value &location = doc["location"];
    string name = location["name"].GetString();
    float coord_lon = location["lon"].GetFloat();
    float coord_lat = location["lat"].GetFloat();
    string timezone = location["tz_id"].GetString();

    const Value &current = doc["current"];
    float currentTemp = current["temp_c"].GetFloat();
    float humidity = current["humidity"].GetFloat();
    float uv = current["uv"].GetFloat();
    float feelslike = current["feelslike_c"].GetFloat();

    const Value &condition = current["condition"];
    string weatherDescription = condition["text"].GetString();

    const Value &forecastday = doc["forecast"]["forecastday"][0];
    const Value &day = forecastday["day"];
    float minTemp = day["mintemp_c"].GetFloat();
    float maxTemp = day["maxtemp_c"].GetFloat();

    // Display weather information
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "-" << reset;
        if (i == 101)
            cout << cyan << "-" << reset << endl;
    }
    cout << orange << "Location: " << name << reset << endl;
    cout << blue << "Coordinates - Latitude: " << coord_lat << reset << endl;
    cout << blue << "Coordinates - Longitude: " << coord_lon << reset << endl;
    cout << orange << "Timezone: "<< timezone << reset << endl;
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "-" << reset;
        if (i == 101)
            cout << cyan << "-" << reset << endl;
    }
    cout << blue << "Weather Description: " << weatherDescription << reset << endl;
    cout << orange << "Current Temperature: " << currentTemp << "°C" << reset << endl;
    cout << blue << "Feels Like: " << feelslike << "°C" << reset << endl;
    cout << orange << "Minimum Temperature: " << minTemp << "°C" << reset << endl;
    cout << blue << "Maximum Temperature: " << maxTemp << "°C" << reset << endl;
    cout << orange << "Humidity: " << humidity << "%" << reset << endl;
    cout << blue << "UV: " << uv << reset << endl;
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "-" << reset;
        if (i == 101)
            cout << cyan << "-" << reset << endl;
    }
}

// Function to get user input
string UserInput()
{
    int i;
    string choice, location;

    cout << green << "What would you like to enter, location or coordinates? (enter 'l' for location and 'c' for coordinates): " << reset; // Asking to enter either location or coordinates
    cin >> choice;
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "-" << reset;
        if (i == 101)
            cout << cyan << "-" << reset << endl;
    }

    if (choice == "l" || choice == "c")
    {
        if (choice == "l")
        {
            cout << green << "Please enter location: " << reset;
            cin >> location;
        }
        else if (choice == "c")
        {
            cout << green << "Please enter coordinates (input format = latitude,longitude):" << reset;
            cin >> location;
        }
    }
    else
    {
        cout << red << "*** invalid input - try again ***" << reset << endl;
        location = UserInput(); // Function will be recalled incase user input is invalid
    }

    return location;
}

int main()
{
    int i;
    string location, response;

    // Welcome message
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "=" << reset;
        if (i == 101)
            cout << cyan << "=" << reset << endl;
    }
    for (i = 0; i <= 32; i++)
    {
        cout << " ";
        if (i == 32)
            cout << yellow << "Welcome to Weather Forecast Application" << reset << endl;
    }
    for (i = 0; i <= 101; i++)
    {
        cout << cyan << "=" << reset;
        if (i == 101)
            cout << cyan << "=" << reset << endl;
    }

    // Calling function for user input
    location = UserInput();

    // Construct URL for HTTP request
    string url = "http://api.weatherapi.com/v1/forecast.json?key=" + API_Key + "&q=" + location + "&days=1&aqi=no&alerts=no";

    // Loop to recall the function if HTTP response is invalid due to incorrect user input
    while (true)
    {

        // Make HTTP request
        response = HTTPRequest(url);

        // Check if the HTTP request was successful
        if (!response.empty() && response != "Invalid location/coordinates - please try again.")
        {
            break;
        }
        else
        {
            cout << "Invalid location/coordinates - please try again: ";
            cin >> location;

            // Update the URL
            url = "http://api.weatherapi.com/v1/forecast.json?key=" + API_Key + "&q=" + location + "&days=1&aqi=no&alerts=no";
        }
    }

    WeatherData(response); // Calling function to parse the received JSON data

    return 0;
}
