## Run
### Start Fake Server
```sh
python fake_serv.py
```
### Run on Terminal
```sh
python -m locust -f ./locustfile.py --host 'http://0.0.0.0:5000' --users 1 --spawn-rate 1.0 --headless
```
