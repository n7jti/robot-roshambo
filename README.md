# robot-roshambo

This is the repository for the LIT (Learn Innovate Tinker) project to create an army of semi-intelligent robots that play rock-paper-scissors.

The robots are built using the Raspberry Pi Pico (RP2040). They play rock-paper-scissors over the serial port, and eventually using an IR Transmitter/reciever pair.  Here's the basic schedule.

1. Get the hardware nailed down and built over the summer
2. Also over the summer, get the basic software framework in place so all competitors need to do is build their AI.
3. Be ready in September for the MSFT Hackathon which will give competitors a chance to build their Roshambo AI.
4. In October (the MSFT Giving Campaign) a competition will be held and the winner can choose from among a list of charities to get the winnings.

## Prerequisites

Getting started instructions are in the [Pico-WSL2](https://github.com/n7jti/pico-wsl2) repository. Follow these instructions to get a WSL2 and VSCode based development environment that can do hardware debugging using the Picoprobe firmware.

### Development Container

Alternatively, you can avoid local dependency installation as this repository includes a *Visual Studio Code Remote - Containers / Codespaces* [development container](https://github.com/n7jti/robot-roshambo/tree/main/.devcontainer).

- For [Remote - Containers](https://aka.ms/vscode-remote/download/containers), use the **Remote-Containers: Open Repository in Container...** command which creates a Docker volume for better disk I/O on macOS and Windows.
- For Codespaces, install the [GitHub Codespaces](https://marketplace.visualstudio.com/items?itemName=GitHub.codespaces) extension in VS Code, and use the **Codespaces: Create New Codespace command**.

## Flashing the Pico

<!-- TODO: -->

## Debugging

<!-- TODO: debugging with pico probe and openocd -->
