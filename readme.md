# About
This repository is part of a coding challenge. There are 2 windows console applications developed using C++: The server and a client that communicate via Named pipes.

# Time management
Coded from 05:00 PM (BRT) to 09:00 PM (BRT) on Saturday 14/07

Coded from 06:30 PM (BRT) to 10:30 PM (BRT) on Sunday 15/07

Total: 8 hours.

# Explanation
I decided to implement everything based on classes because it makes the code more manageable, maintainable and easy to understand. There are 3 main classes that represents each part of the requested solution.

## Client
It's the class that represents the client application and contains every action that it can do on the server. Since the Client will be always dependent on the server, it checks everything in its constructor, generating an authentication key, and verifying the server availability right away. It can read and write data on the server pipe.


## Server
The class that represents the server application. The constructor here just takes the name of the pipe making the initialization function ` Server::startServer() `. It also checks for valid keys every time a client tries to connect, making the communication more secure. Stores all data a client provides, being capable of retrieving it afterwards. When a client connects, the Server always wait for an action coming from him.


## Data
As the name says, its the class responsible for holding the data that goes through the pipe. Currently has only the `name` attribute. It also has operators `<<` and `=` overloaded for making the cout's and variable attributions easier. The method toString() also makes it easier to use since the pipe functions I implemented accept only std::strings as parameters as I decided to not use templates because of the time limit of this challenge.