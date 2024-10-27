#include <fftw3.h>
#include <SFML/Graphics.hpp>
#include <cmath>
// #include <thread>  TODO: figure out multithreading :woozy:

int main() {
    constexpr int SAMPLE_COUNT = 512;
    constexpr int SAMPLE_FREQUENCY = SAMPLE_COUNT*2;
    constexpr int WINDOW_X = 1024;
    constexpr int WINDOW_Y = 720;

    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SAMPLE_FREQUENCY);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SAMPLE_FREQUENCY);

    fftw_plan plan = fftw_plan_dft_1d(SAMPLE_FREQUENCY, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Generating sample data using a sine wave
    for (int i = 0; i < SAMPLE_FREQUENCY; i++) {
        // Real
        in[i][0] = sin(2 * i * M_PI * 50.0 / SAMPLE_FREQUENCY) + sin(2 * i * M_PI * 35 / SAMPLE_FREQUENCY);
        // Imaginary
        in[i][1] = 0.0;
    }

    // FFT!
    fftw_execute(plan);
    
    // Creating a render window
    sf::RenderWindow window(sf::VideoMode(WINDOW_X,WINDOW_Y), "SillyFFT");
    window.setPosition(sf::Vector2i(0,0));
    
    // Creating a vertex array for sine data
    sf::VertexArray sineData(sf::LineStrip, SAMPLE_COUNT);
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        sineData[i] = sf::Vector2f(2*i,WINDOW_Y/2 - in[i][0]*100);
    }

    // Creating a vertex array for FFT data
    sf::VertexArray fftData(sf::LineStrip, SAMPLE_COUNT);
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        double freq = i;
        double magnitude = std::sqrt(std::pow(out[i][0],2) + std::pow(out[i][1],2));
        fftData[i] = sf::Vector2f(2*freq, WINDOW_Y - 50 - magnitude); // 50 chosen arbitrarily to provide an offset from the bottom for clarity   
    }

    bool showSine = true; // Used to switch between displaying sine and fft

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                showSine = !showSine;
            }
        }

        window.clear();
        if (showSine) {
            window.draw(sineData);
        } else {
            window.draw(fftData);
        }
        window.display();
        
    }

    // Cleaning up (C library moment)
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return 0;
}