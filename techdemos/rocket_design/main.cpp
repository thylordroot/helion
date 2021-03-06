#include <iostream>
#include <string>
#include <helion/mesh.h>
#include <GLFW/glfw3.h>

// Needed for thread management
#include <thread>
#include <chrono>



int main() {
	int choices[3];
	std::cout<<"If you want: a pointed cockpit, enter 1; a rounded cockpit, enter 2 or for a flat cockpit, enter 3\n";
	std::cin >> choices[0];
	std::cout<<"If you want: a tall thin fuel tank, enter 1; a short fat fuel tank, enter 2 or a toroidal fuel tank, enter 3\n";
	std::cin >> choices[1];
	std::cout<<"If you want: a standard size engine, enter 1; a large size engine, enter 2 or a jet engine, enter 3\n";
	std::cin >> choices[2];

	std::string filenames[] = {"pointed", "rounded", "flat", "tall", "short", "toroidal", "standard", "fat", "jet"};

	render::Mesh rocket[3];
	double height = 0;
	for(int i = 0; i < 3; ++i) {
		if(!rocket[i].load("data/"+(filenames[(i*3)+choices[i]-1])+".obj")) {
			std::cout<<"Error! Files not loaded correctly.\n";
			return 1;
		}
		height += rocket[i].height();
	}

    /* Attempt to initialize GLFW */
	if (!glfwInit()) {
        exit(EXIT_FAILURE);
	}

    /* Set any hits we need for our windows */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

    /* Windowed mode, no parent window */
    GLFWwindow* root = glfwCreateWindow(800, 600, "Rocket Designer", NULL, NULL);
    if (!root) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	while(!glfwWindowShouldClose(root)) {
        /* Don't rape the CPU - ~60Hz (we should really be updating on vsync) */
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		for(int i = 0; i < 3; ++i) {
            std::cout << "i=" << i << std::endl;

			double shift = 0;
			for(int j = 0; j < i; ++j) {
				shift += rocket[j].height();
			}
			rocket[i].render(2/height, {0, 1 - 0.5*(shift/height) - 0.5*(rocket[i].height()/height), 0});
		}
		glfwSwapBuffers(root);
	}
	return 0;
}
