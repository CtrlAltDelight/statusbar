import requests
import json
import time

# Global constants
MAX_API_CALLS = 1000
CACHE_DURATION = 15 * 60 # The amount of time in seconds to wait between calling the API again.
CACHE_FILE = "cache.json"

def update_api_counter(api_file):
    # Get the current number of API calls from file
    data = read_file(api_file)
    if data is None: # If the file did not exist, we will create the file.
        # This may be dangerous if you have already been making API calls 
        # and you are worried about going over the limit.
        data = 0
    else:
        data = int(data)

    # Make sure we won't go over our call limit
    if data + 1 > MAX_API_CALLS:
        raise RuntimeError("Exceeded maximum number of API calls")

    # Increment the number of api calls by 1
    with open(api_file, 'w') as f:
        f.write(str(data + 1));

def read_file(file):
    try: 
        with open(file, 'r') as f:
            return f.read()
    except IOError:
        print(f"Warning: Could not open '{file}' file.")
        return None

def get_cached_data():
    cached_data = read_file(CACHE_FILE)
    if cached_data is not None:
        return json.loads(cached_data);

    # If the cache does not exist, return a time that will cause a new API CALL.
    return {"time": 0, "data": None}


def get_weather_icon_from_id(weather_id):
    # More information on weather codes here: https://openweathermap.org/weather-conditions
    if(200 <= weather_id < 300): # Thunderstorm
        return "󰖓"
    elif(300 <= weather_id < 400): # Drizzle
        return "󰖗"
    elif(500 <= weather_id < 600): # Rain
        return "󰖖"
    elif(600 <= weather_id < 700): # Snow
        return "󰖘"
    elif(700 <= weather_id < 800): # Atmosphere (fog, other)
        return "󰖑"
    elif(weather_id == 800): # Clear
        return "󰖙"
    elif(801 <= weather_id < 900): # Clouds
        return "󰖐"

def get_weather():
    # Check if the cached data is still fresh.
    current_time = time.time()
    cache = get_cached_data()
    if current_time - cache['time'] < CACHE_DURATION:
        # Cached data is still fresh. Use that.
        return cache['data']

    # Cached data is stale, make a new API call.

    # Get secrets from secrets.json
    secrets_filename = "secrets.json"
    raw_secrets = read_file(secrets_filename)
    if raw_secrets is None:
        return
    secrets = json.loads(raw_secrets)

    # See if we are at out usage limit for the API
    api_file = "api_usage.txt"
    update_api_counter(api_file)

    # Build URL for API call
    url = f"https://api.openweathermap.org/data/2.5/weather?lat={secrets['LATITUDE']}&lon={secrets['LONGITUDE']}&appid={secrets['API_KEY']}&units=imperial"

    # Perform API call
    response = requests.get(url, params=secrets)
    data = response.json()

    # Cache new data
    with open(CACHE_FILE, 'w') as f:
        json.dump({'time': current_time, 'data': data}, f)

    return data

# Main
weather_data = get_weather()

# Print the temperature and icon representing the weather
print(round(weather_data["main"]["temp"]), end=" ")
print(get_weather_icon_from_id(weather_data["weather"][0]["id"]), end=" ")
