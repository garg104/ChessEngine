import requests

time = []
print ("Enter game conditions: ")
while True:
    url = "http://18.234.145.132:5000"
    data = input()
    response = requests.post(url, data)
    time.append(response.elapsed.total_seconds())
    print(response.text)
    if "Win" in response.text:
        break

print (time)

with open("time.time", "w") as f:
    f.write("\n".join(str(time)))
