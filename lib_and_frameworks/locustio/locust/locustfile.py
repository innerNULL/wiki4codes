# -*- coding: utf-8 -*-
# file: stress_test.py
# date: 2023-02-09


import time
from locust import HttpUser, task, between


class QuickstartUser(HttpUser):
    wait_time = between(1, 5)

    @task
    def hello_world(self):
        self.client.get("/")
