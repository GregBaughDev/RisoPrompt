# RisoPrompt

### A MacOS application built with Qt for interacting with Google Gemini LLMs

**Requires >= Qt6**

Allows you to interact with Google Gemini LLM's through a custom, [Risograph](https://en.wikipedia.org/wiki/Risograph) inspired, GUI application. Built with Qt, it interacts with Gemini with RPC.

#### Features:

- Save and load conversations locally
- Update model and API key easily
- Copy conversations to the clipboard

On loading up the application you'll be prompted to store the model you want to use (example format: `models/gemini-2.0-flash`) and your api key (accessed from your Google Gemini API keys). I'm working on adding all the models to a dropdown so you don't need to manually add it. This is then stored in the embedded DB and you can update it through the `Model` option.

I've been learning C++ in my spare time and wanted to learn how to build a GUI application with Qt. I also wanted my own interface for interacting with LLMs on my machine.

#### Instructions for compiling

I used Qt open source as I wanted to learn the framework. You'll need Qt6 installed locally and will also need to manually compile the classes and gRPC client files from the `generative_service_client` Google proto file. You can use the [qtprotobufgen & qtgrpcgen](https://doc.qt.io/qt-6/qtgrpc-index.html) protoc plugins to do this. I wanted to automate this through my qmake file but I couldn't find a way to do it (the docs only specific cmake) but if you know how, let me know as it's far easier than hand compiling each required file. I've been building directly from Qt Creator.

#### Font

I used [Terminal Grotesque](https://velvetyne.fr/fonts/terminal-grotesque/) in the project. Credit to [Raphaël Bastide](https://velvetyne.fr/authors/raphael-bastide/) and [Velvetyne Type Foundry](https://velvetyne.fr/) for the creation of this font.
