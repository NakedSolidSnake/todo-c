#!/bin/bash

curl -X DELETE -s http://localhost:1234/remove?id=1 | jq .