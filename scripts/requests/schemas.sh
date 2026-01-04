#!/bin/bash

TYPE=$1
echo $TYPE

curl -X GET -s "http://localhost:1234/schemas?filter=${TYPE}" | jq .