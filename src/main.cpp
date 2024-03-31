#include <iostream>
#include <string>
#include "../curl/curl.h"
#include "../rapidjson/document.h"

using namespace std;
using namespace rapidjson;

const string API_Key = "5ba9593f80c849a0b3403917242603"; // Declaring API Key as a constant

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
            cerr << "Failed to send HTTP request: " << curl_easy_strerror(res) << endl;
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
        cerr << "Failed to initialize libcurl." << endl;
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
        cerr << "Error parsing JSON data: " << doc.GetParseError() << endl;
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
        cout << "-";
        if (i == 101)
            cout << "-" << endl;
    }
    cout << "Location: " << name << endl;
    cout << "Coordinates - Latitude: " << coord_lat << endl;
    cout << "Coordinates - Longitude: " << coord_lon << endl;
    cout << "Timezone: "<< timezone << endl;
    for (i = 0; i <= 101; i++)
    {
        cout << "-";
        if (i == 101)
            cout << "-" << endl;
    }
    cout << "Weather Description: " << weatherDescription << endl;
    cout << "Current Temperature: " << currentTemp << "°C" << endl;
    cout << "Feels Like: " << feelslike << "°C" << endl;
    cout << "Minimum Temperature: " << minTemp << "°C" << endl;
    cout << "Maximum Temperature: " << maxTemp << "°C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "UV: " << uv << endl;
    for (i = 0; i <= 101; i++)
    {
        cout << "-";
        if (i == 101)
            cout << "-" << endl;
    }
}

// Function to get user input
string UserInput()
{
    int i;
    string choice, location;

    cout << "What would you like to enter, location or coordinates? (enter 'l' for location and 'c' for coordinates): "; // Asking to enter either location or coordinates
    cin >> choice;
    for (i = 0; i <= 101; i++)
    {
        cout << "-";
        if (i == 101)
            cout << "-" << endl;
    }

    if (choice == "l" || choice == "c")
    {
        if (choice == "l")
        {
            cout << "Please enter location: ";
            cin >> location;
        }
        else if (choice == "c")
        {
            cout << "Please enter coordinates (input format = latitude,longitude):";
            cin >> location;
        }
    }
    else
    {
        cout << "*** invalid input - try again ***" << endl;
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
        cout << "=";
        if (i == 101)
            cout << "=" << endl;
    }
    for (i = 0; i <= 32; i++)
    {
        cout << " ";
        if (i == 32)
            cout << "Welcome to Weather Forecast Application" << endl;
    }
    for (i = 0; i <= 101; i++)
    {
        cout << "=";
        if (i == 101)
            cout << "=" << endl;
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
