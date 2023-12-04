import requests

print ("Enter game conditions: ")
while True:
    url = "http://34.207.98.253:5000"
    data = input()
    response = requests.post(url, data)
    print(response.text)
    if "Win" in response:
        break
