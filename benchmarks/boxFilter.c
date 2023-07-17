#include "../src/include/smoothing/box.h"
#include "../src/include/image.h"
#include "../src/include/logging.h"

#include <time.h>
#include <stdio.h>


int main() {
    Image img = {.path = "../data/img1.jpg"};
    cv_load_image(&img);

    for (int i = 1; i < 4; i++) {
        Image *cpy = cv_deepcopy_image(&img);
        
        clock_t start_time = clock();
        cv_apply_box_filter(cpy, i * 3);
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        
        cv_free_deepcopy_image(cpy);

        CV_INFO("filter took %f for kernelSize %d", time_taken, i * 3);
    }

    cv_free_image(&img);
}
