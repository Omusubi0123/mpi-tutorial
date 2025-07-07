#!/bin/sh
# tutorial/pagerank/にvenvを作成

python3 -m venv venv
. venv/bin/activate
pip install --upgrade pip
pip install numpy pandas matplotlib networkx
