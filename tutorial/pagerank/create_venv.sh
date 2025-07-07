#!/bin/sh

python3 -m venv venv
. venv/bin/activate
pip install --upgrade pip
pip install numpy pandas matplotlib networkx
