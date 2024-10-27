## ABOUT:
A very simple program that uses FFTW3 to perform a FFT on a sin wave. It's just for fun. Also uses SFML to render data. Use ESC to switch between displaying
the original sin wave.


## SETUP:
Pretty straightforward, uses GNU make to automate compilation and G++ to compile. Requires SFML and FFTW3. This project was made using WSL 2.2.4.0, but it can probably be adapted to other systems with very little modification.

SFML can be installed using `sudo apt install libsfml-dev` <br />
FFTW3 can be installed using `sudo apt install libfftw3-dev` <br />
GNU Make and G++ can be installed using `sudo apt install build-essential` <br />

After installing the required dependencies, the program can be compiled by running `make` in the project directory.
