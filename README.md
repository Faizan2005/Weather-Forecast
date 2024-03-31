# Weather Forecast Application

This is a command-line interface (CLI) software that receives input from the user to provide metadata of the specified location.

• This program utilizes an Application Programming Interface (API) service to retrieve metadata from the server.

• The core of this software is built upon the C++ language.

## Preview

The Weather Forecast Application is a tool designed to provide users with accurate and up-to-date weather information. Using the 'Real-time Weather API' from https://www.weatherapi.com/, this application offers a seamless experience for users to access weather data based on their specified location or coordinates.

### Key Points

1. The application allow users to easily input their desired location or coordinates to obtain weather forecasts.

2. With location as input, HTTP request is sent to the API service (www.weatherapi.com here) in return for weather data using 'cURL' library.

3. The received data is in JavaScript Object Notation (JSON) that is parsed and then displayed in readable format using RapidJSON library.

### A diagram outlining the steps involved in executing the software:
![Screenshot 2024-03-31 201803](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/511ea64a-5441-4bdc-a04f-81b8867bd7ac)

## How to Install and Run

### For Ubuntu (Linux)
Install cURL in the system
 ```
 sudo apt update
 ```
 ```
 sudo apt install curl
 ```
Install libcurl package
```
 sudo apt install libcurl4
```
To verify installation 
```
 curl --version
```
Now, since cURL is installed in the system, download .zip file of the project from github repository.  Extract the folder.
Navigate to the main directory of the project and open terminal in that directory.

![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/03dbb86e-90de-49ec-88d0-793c2a36580f)

To create the executable file enter the following command.
```
g++ -o bin/weather src/main.cpp -lcurl
```
A new file will be created in 'bin' folder which we will be executing to run the software
``` 
./bin/weather
```
This will run the software and now to use it, enter 'l' or 'c' based on what would you like to enter as an user input (location or coordinates).
Then after entering location name or coordinates, weather details will be displayed.

Error Handling : Incase any error occurred due to invalid user input, user will be asked to re-enter the correct input.

### For Windows
Install cURL in the system

Go to the official curl website: https://curl.haxx.se/windows/.
Download the appropriate version of curl for your Windows system. Downloading .zip file is recommended. Download and extract it.

Set up environment variables:

 To use curl from any directory in the command prompt, you might want to add their installation directories to the system's 
 PATH environment variable.

 Right-click on "This PC" or "My Computer" and select "Properties".
 Click on "Advanced system settings".
 In the System Properties window, click on the "Environment Variables" button.
 Under "System variables", find the "Path" variable and select "Edit".
 Add the directories containing 'curl' executable to the PATH. Executable file is generally in the 'bin' folder of 'curl' folder.
 Click "OK" to save the changes.

Verify cURL installation by  typing ```curl --version``` and ```where curl``` to check the path of the curl directory.

Now,  download .zip file of the project from github repository. 
Navigate to the main directory of the project and open terminal in that directory.

![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/03dbb86e-90de-49ec-88d0-793c2a36580f)

To create the executable file enter the following command.
```
g++ -o bin\weather src\main.cpp -I "curl" -L "lib" -lcurl
```
A new file (weather.exe) will be created in 'bin' folder which we will be executing to run the software.
``` 
.\bin\weather
```
This will run the software and now to use it, enter 'l' or 'c' based on what would you like to enter as an user input (location or coordinates).
Then after entering location name or coordinates, weather details will be displayed.

![image](https://github.com/Faizan2005/Weather-Forecast/assets/146985659/d715ccca-aff6-4c1a-b7bf-aeef0319d136)

Error Handling : Incase any error occurred due to invalid user input, user will be asked to re-enter the correct input.

## main.cpp
main.cpp is the main code file of the software built upon C++. 
There are 5 functions in total in main.cpp. Their brief explanation is as follows:

1. write_callback(): This is a callback function used by the 'libcurl' library to write the data received from an HTTP request. It takes four parameters: a pointer to a block of memory containing the received data, the size of the block of memory, the number of members in the block of memory, and a pointer to a 'string' object to store the received data. The function appends the received data to the 'string' object and returns the number of bytes written.

2. HTTPRequest(); This function sends an HTTP request to the Weather API to get the current weather data for a given location or coordinates, and returns the response data as a string. It initializes the 'libcurl' library, sets the URL for the HTTP request, and sets the callback function 'write_callback' to receive the data from the HTTP response. The 'libcurl' library is then used to send the HTTP request and receive the response. If the HTTP request is successful, the function returns the response data as a string. If the request fails, the function returns an error message. If the error is due to invalid user input, it is redirected to 'main()' function to re-enter the location.

3. WeatherData(): This function parses the JSON data received from the HTTP request and displays the weather data. It takes a string parameter httprequest which contains the JSON data. 

4. UserInput(): This function gets the user input for the location or coordinates. It takes no parameters and returns a string that contains the user input.

5. main(): This is the main function of the program. It initializes the program, displays welcome messages, calls the UserInput function to get the user input, calls the HTTPRequest function to get the weather data, calls the WeatherData function to display the weather data, and finally cleans up and exits the program.

## How I completed the project (my thought process and issues faced during the journey): 

• Initially I searched about "Data Scraping" and how does a weather software works. There were various other terms I wasn't familiar about like API, JSON, Parsing and many other. So, the first step was to know about these, watched various youtube videos, visited various websites. I planned to do it in Ubuntu (Linux).

• I got familiar about how this weather software will work, wrote down a brief process about the execution of the code, about how HTTP request will be sent, what will be the role of API and how parsing will be done. Then I finalized that I will be using API to make this software.  I planned to do it in 3 phases.
 1. writing the entire code and only using name of location as user input.
 2. also including coordinates as user input to run the code
 3. finally doing error handling in the code, like if user provides wrong location or coordinates, an error message will be shown and 
     user will be asked again to enter the inputs.

• Then I created API account in https://openweathermap.org/api to access free API Key. API Key is necessary to access weather info from the server.

• Firstly, I wrote main() function. Entered basic commands like asking user for inputs, and calling other functions. Then I wrote HTTPRequest() function, I found it very difficult to write the code of this function as there were various curl library commands used, so I watched youtube videos and other resources to know the correct format of a curl based HTTP request function. Then I wrote WeatherData() function which was to be used in parsing the JSON response we got from HTTPRequest(). I required rapidjson library, so I installed it. The syntax of rapidjson library to extract JSON data and convert to readable form wasn't that difficult.

• When all functions were written, and I had to compile the code, errors appeared like "fatal error: curl/curl.h: No such file or directory"   . I had to search to find the solutions and finally after changing some file path and correctly adding "preprocessor" commands, it started working.

• While running, there was again an issue coming, 'minimum' and 'maximum' temperature were coming same, it was because of the feature this API service was providing, so I changed the API service to "https://www.weatherapi.com/", they had distinct min-max temperatures and other data as well like UV, Time zone etc.

• Since the code was working fine in Ubuntu, I tried to run it in windows using its corresponding terminal commands, but "fatal error: curl/curl.h: No such file or directory" this issue was coming up. I tried different methods to solve it like by adding path of curl.exe to system variables or adding header and library files of curl in project folder. The issue was occurring because main.cpp wasn't able to locate curl.h header file. After learning more about adding libraries in project. I fixed the issue, the problem was that the path preprocessor command showing wasn't correct with respect to the directory structure of the project. I changed it form "#include <curl/curl.h>" to "#include <../curl/h>". The terminal commands that I was using also had some mistake that I correct. This fixed my issue.

# Lists of Issues faced and fixed 
1. "fatal error: curl/curl.h: No such file or directory" in Ubuntu.
2. same max-min temperature in output.
3. windows compatibility issue for curl library.
4. issue in terminal commands to run the code. I was entering "g++ -o bin\weather src\main.cpp -I\curl -lcurl" instead of "g++ -o bin\weather src\main.cpp -I "curl" -L "lib" -lcurl"

  




