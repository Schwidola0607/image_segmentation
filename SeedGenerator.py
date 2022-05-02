import cv2
import numpy as np
import sys

# Declare foreground (fg) and background (bg) descriptors
fg_color, bg_color = (0, 255, 0), (0, 0, 255)
fg_code, bg_code = 1, 2
scale_factor = 10

def get_seeds(image):

    def draw_seeds(x, y, seed_type):
        """ Visually draw the seeds on the image and stores them in the seeds array """
        # Draws either foreground or background seeds
        color = fg_color if seed_type == "fg" else bg_color
        code  = fg_code  if seed_type == "fg" else bg_code
        # How big to draw the circles (only for visual purposes)
        radius = scale_factor
        cv2.circle(image, (x, y), radius, color, -1)
        cv2.circle(seeds, (x//scale_factor, y//scale_factor), radius//scale_factor, code, -1)

    def mouse_event(event, x, y, flags, seed_type):
        """ Checks for clicks on the image and determines what seeds have been placed """
        global mouse_down
        # Single mouse click
        if event == cv2.EVENT_LBUTTONDOWN and not mouse_down:
            mouse_down = True
            draw_seeds(x, y, seed_type)
        elif event == cv2.EVENT_LBUTTONUP:
            mouse_down = False

    def receive_input(seed_type):
        """ Receives input from the user to place either foreground or background seeds """
        global mouse_down
        mouse_down = False
        window_name = "Choose Foreground Seeds" if seed_type == "fg" else "Choose Background Seeds"
        cv2.namedWindow(window_name, cv2.WINDOW_AUTOSIZE)
        cv2.setMouseCallback(window_name, mouse_event, seed_type)
        # While the escape key hasn't been pressed, display the image
        while (cv2.waitKey(1) & 0xFF != 27):
            cv2.imshow(window_name, image)
        cv2.destroyAllWindows()
    
    # Initialize seeds and colored image (previously grayscale)
    seeds = np.zeros(image.shape, dtype="uint8")
    image = cv2.cvtColor(image, cv2.COLOR_GRAY2RGB)

    # Receive input for fg and bg seeds
    receive_input("fg")
    receive_input("bg")

    return seeds, image

if __name__ == "__main__":
    # Gets the image path from the user
    image_path = input("Please input the image path: ")
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    while(image is None):
        image_path = input("Invalid path. Please input the image path: ")
        image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    
    # Once it successfully loads the image, get the obtain the seeds and seeded image
    print("Image successfully loaded, please select background and foreground seeds")
    image = cv2.resize(image, (32*scale_factor, 32*scale_factor))
    seeds, image = get_seeds(image)

    # Write valid seeds to file
    f = open("input.txt", "w")
    f.write(image_path + "\n")
    r, c = seeds.shape
    for i in range(r):
        for j in range(c):
            if seeds[i][j] == fg_code:
                f.write(str(i) + " " + str(j) + "\n")
    f.write("-1 -1\n")
    for i in range(r):
        for j in range(c):
            if seeds[i][j] == bg_code:
                f.write(str(i) + " " + str(j) + "\n")
    f.write("-1 -1\n")
    f.close()
    print("Successfully wrote seed input into input.txt")

    # Write the seeded image to a png
    cv2.imwrite("Output/SeededImage.png", image)
    print("Successfully wrote seeded image to Output/SeededImage.png")


