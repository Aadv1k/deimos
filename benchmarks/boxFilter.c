#include "../src/include/smoothing/box.h"
#include "../src/include/image.h"
#include "../src/include/logging.h"

#include <time.h>
#include <stdio.h>

#define MAX_SUITS 3
#define START_AT 1

//[INFO] filter took 1.406000 for kernelSize 3
//[INFO] filter took 4.783000 for kernelSize 6
//[INFO] filter took 10.412000 for kernelSize 9

//[INFO] the filter took 0.830000 for kernelSize 3
//[INFO] the filter took 3.928000 for kernelSize 6
//[INFO] the filter took 6.213000 for kernelSize 9

//[INFO] the filter took 0.822000 for kernelSize 3
//[INFO] the filter took 3.884000 for kernelSize 6
//[INFO] the filter took 6.238000 for kernelSize 9

int main() {
    Image img = {.path = "../../d1/ofkqvd355h.jpg"};
    cv_load_image(&img);

    for (int i = START_AT; i < MAX_SUITS + START_AT; i++) {
        Image *cpy = cv_deepcopy_image(&img);
        
        clock_t start_time = clock();
        cv_apply_box_filter(cpy, i * 3);
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        
        cv_free_deepcopy_image(cpy);

        CV_INFO("the filter took %f for kernelSize %d", time_taken, i * 3);
    }


    cv_write_image(&img, "../bin/output.jpg");

    cv_free_image(&img);
}
