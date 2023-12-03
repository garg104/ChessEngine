import requests

print ("Enter game conditions: ")
while True:
    url = "http://localhost:8080"
    data = input()
    response = requests.post(url, data)
    print(response.text)
    if "Win" in response:
        break