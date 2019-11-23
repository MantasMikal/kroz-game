# Kroz
Welcome to the readme file for Kroz
Kroz is a text based retro game that takes inspiration from the popular game [Zork](https://en.wikipedia.org/wiki/Zork)

The game was developed as part of University curriculum.
## Authors
* Dom
* Jack
* Mantas
* Joe
* Abbas


## Getting Started
Please follow the steps to clone the repo, if you need help with git basics just have a look at [this](https://try.github.io)
### Prerequisites
* OpenSSL and Dev packadge 
* sqlite3 and Dev packadge 
#### Linux
``` bash
sudo apt install sqlite3 libsqlite3-dev openssl libssl-dev
```
#### MacOS
You need to install [brew](https://brew.sh/).
```bash
brew install sqlite3 openssl
```
### Clone the Repo
```bash
git clone https://github.coventry.ac.uk/eggintod/b2Game.git
cd b2Game
```
### Compiling
```
g++ --std=c++14 *.cpp -o output -lsqlite3 -lcrypto
```
### Running
```
./output
```

## ERD
![](https://i.imgur.com/GZyQEQ0.png)



