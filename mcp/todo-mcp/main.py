import requests

def main():
    value = requests.get("http://localhost:1234/health")
    print(value.text)


if __name__ == "__main__":
    main()
