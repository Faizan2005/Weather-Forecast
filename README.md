# Weather Forecast Application

Welcome to the Weather Forecast Application README! This command-line interface (CLI) software serves to provide users with meta-data of specified locations regarding weather conditions.

## Overview

This application leverages an Application Programming Interface (API) service to retrieve metadata from the server. Built at its core using the C++ language, it offers a seamless experience for users to access real-time weather data.

## Key Features

- Easy input for desired location or coordinates to obtain weather forecasts.
- Utilizes HTTP requests sent to the API service for weather data retrieval.
- Parses received data in JavaScript Object Notation (JSON) and presents it in a readable format.

## Execution Flow Diagram

![Screenshot 2024-03-31 201803](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/511ea64a-5441-4bdc-a04f-81b8867bd7ac)

## Installation and Execution

### For Ubuntu (Linux)

Ensure cURL is installed:

```bash
sudo apt update
sudo apt install curl
sudo apt install libcurl4
curl --version
```

To execute the software:

1. Download the .zip file from the GitHub repository.
2. Extract the folder then go to the main directory of the project and open the terminal from within that directory.                                  ![Screenshot from 2024-03-31 23-36-54](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/d45b7605-d863-47a2-933a-c5e58244097e)
3. Compile the code:

```bash
g++ -o bin/weather src/main.cpp -lcurl
```

4. Run the executable:

```bash
./bin/weather
```
This will run the software and now to use it, enter 'l' or 'c' based on what would you like to enter as an user input (location or coordinates). Then after entering location name or coordinates, weather details will be displayed.
![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/3350a85b-ed30-49f7-9eca-4389f754022c)

### For Windows

Install cURL:

Download from [Curl's official website](https://curl.haxx.se/windows/).

Extract and set up environment variables:

1. Right-click on "This PC" or "My Computer" and select "Properties".
2. Click on "Advanced system settings".
3. In the System Properties window, click on the "Environment Variables" button.
4. Under "System variables", find the "Path" variable and select "Edit".
5. Add the directories containing 'curl' executable to the Path. The executable file is generally in the 'bin' folder of 'curl' folder.
6. Click "OK" to save the changes.

Verify cURL installation:

```bash
curl --version
where curl
```

Execution:

1. Download the .zip file from the GitHub repository.
2. Extract the folder then go to the main directory of the project and open the terminal from within that directory.                                 ![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/03dbb86e-90de-49ec-88d0-793c2a36580f)
3. Compile:

```bash
g++ -o bin\weather src\main.cpp -I "curl" -L "lib" -lcurl
```

4. Run the executable:

```bash
.\bin\weather.exe
```
This will run the software and now to use it, enter 'l' or 'c' based on what would you like to enter as an user input (location or coordinates).
Then after entering location name or coordinates, weather details will be displayed.

![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/d715ccca-aff6-4c1a-b7bf-aeef0319d136)

### Error Handling

In case any error occurred due to invalid user input, user will be asked to re-enter the correct input.

## Code Structure Explanation

Let's dive into understanding the structure of the main.cpp file, which forms the heart of the Weather Forecast Application.

### Function Breakdown

#### 1. write_callback():

This function is a callback function utilized by the 'libcurl' library. Its role is to handle the data received from an HTTP request.

**Parameters:**
- ptr: Pointer to the data received.
- size: Size of each data element.
- nmemb: Number of data elements.
- data: Pointer to a string object where the received data is appended.

**Return:**
It returns the total size of the received data.

#### 2. HTTPRequest():

Responsible for making the HTTP request to retrieve weather data and handling the response.

**Parameters:**
- url: The URL for the HTTP request.

**Return:**
It returns the response data as a string.

**Details:**
- Initializes libcurl.
- Sets the URL and callback function for receiving data.
- Performs the request and checks for errors.

#### 3. WeatherData():

Parses the JSON data and displays weather information.

**Parameters:**
- httprequest: The JSON data received from the HTTP request.

**Details:**
- Parses JSON data using the RapidJSON library.
- Extracts location, coordinates, timezone, current weather, temperature, humidity, UV index, and forecasted temperatures.
- Displays the weather information in a readable format.

#### 4. UserInput():

Obtains user input for location or coordinates.

**Return:**
Returns the user input as a string.

**Details:**
- Asks the user whether they want to input a location or coordinates.
- Validates the user input and prompts for re-entry if invalid.

#### 5. main():

Manages the program's flow by calling the necessary functions.

**Details:**
- Displays a welcome message.
- Obtains user input.
- Constructs the URL for the HTTP request.
- Calls function to make the HTTP request
- Handles invalid responses.
- Calls function to parse and display weather data.

This breakdown provides a clear understanding of how each function contributes to the functionality of the Weather Forecast Application.

## Project Completion Journey

### Initial Exploration

- Initially searched about how a weather forecast application works, what all components are required in the code, flow of data. Went through various terms like API, JSON, cURL, RapidJSON, SAX, DOM etc.. Watched YouTube videos and read documentation for cURL and RapidJSON to understand their usage in the context of the project.
- Chose to use C++ because of my familiarity with it.

### Planning and Development Phases

#### Understanding API Integration

- Selected the [OpenWeatherMap](https://openweathermap.org/api) API for its comprehensive weather data coverage and free availability (later changed to https://www.weatherapi.com/ due to output issues)

#### Choosing Libraries

- Decided on cURL for handling HTTP requests and RapidJSON for parsing JSON data.

#### Code Structure Design

- Designed functions in the main.cpp file to handle user input, HTTP requests, JSON parsing, and data display.

### Development Process

#### Writing the Code

- Developed functions to handle user input, make HTTP requests, parse JSON data, and manage program flow in main().
- Struggled initially with syntax errors in integrating cURL and RapidJSON libraries but resolved them over time.

#### Testing and Debugging

- Tested the application in various systems to check it working and identify potential installation issues.
- Faced syntax errors due to the complexity of JSON data structures but gradually gained understanding and resolved them.
- Running it in Windows, I faced lot of compatibility issues, like setting up cURL library which took most of my time fixing it. But that lead me to a deeper understanding of library usage.

### Lists of Issues Faced and Fixed

During the development process, several challenges were encountered, each requiring specific solutions:

1. **"fatal error: curl/curl.h: No such file or directory"** in Ubuntu:

- This error occurred due to the inability to locate the curl header file during compilation.
- **Solution:** Adjusted file paths and preprocessor commands to correctly include the curl library headers.

2. **Same Max-Min Temperature in Output:**

- The application initially displayed identical maximum and minimum temperatures.
- **Solution:** Switched to a different weather API (Real-time Weather API) by https://www.weatherapi.com/ that provided distinct max-min temperatures.

3. **Windows Compatibility Issue for cURL Library:**

- Faced difficulties in ensuring compatibility with Windows environments, particularly with the cURL library.
- **Solution:** Configured environment variables and path settings to resolve compatibility issues. Made changes to paths in preprocessor commands. Also made some changes in terminal commands used to run the code like using **'\'** in windows terminal rather than **'/'**, while adding commands to search headers and library file **'-I curl'** and **'-L lib'** I changed it to **-I "curl"** and **-L "lib"**

4. **Issue in Terminal Commands to Run the Code:**

- Incorrect terminal commands were causing errors during code compilation and execution.
- **Solution:** Adjusted compilation commands and ensured correct syntax to compile and execute the code seamlessly in both Ubuntu and Windows environments.
