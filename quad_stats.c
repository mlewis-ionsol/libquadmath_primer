#include "quad_stats.h"


    // initialize the QData structure
    QData *init_qdata(int count) {
        QData *qdata = malloc(sizeof(QData) + count * sizeof(__float128));
        if (qdata == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        qdata->count = count;
        qdata->data = malloc(count * sizeof(__float128));
        if (qdata->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(qdata);
            exit(EXIT_FAILURE);
        }
        return qdata;
    }
    // free the QData structure
    void free_qdata(QData *qdata) {
        if (qdata != NULL) {
            free(qdata->data);
            free(qdata);
        }
    }
    // All errorhandling includes free_qdata
    // Function to test if a string is a valid __float128 number
    BOOL is_valid_float128(const char *str) {
        char *endptr;
        __float128 val = strtoflt128(str, &endptr);
        if (*endptr != '\0') {
            free_qdata(qdata);
            return FALSE; // Not a valid __float128 number
        }
        return TRUE; // Valid __float128 number
    }
    // Function to read __float128 numbers from a file
    QData *read_qdata_from_file(const char *filename) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            free_qdata(qdata);
            return EXIT_FAILURE;
        }

        QData *qdata = init_qdata(MAX_DATA);
        if (qdata == NULL) {
            fclose(file);
            return EXIT_FAILURE;
        }

        char line[MAX_BUF];
        int count = 0;

        while (fgets(line, sizeof(line), file) != NULL && count < MAX_DATA) {
            line[strcspn(line, "\n")] = '\0'; // Remove newline character
            if (is_valid_float128(line)) {
                qdata->data[count] = strtoflt128(line, NULL);
                count++;
            } else {
                fprintf(stderr, "Invalid __float128 number: %s\n", line);
                free_qdata(qdata);
                fclose(file);
                return EXIT_FAILURE;
            }
        }

        fclose(file);
        qdata->count = count;
        return qdata;
    }
    // Function to sum __float128 numbers
    __float128 sum_qdata(QData *qdata) {
        __float128 sum = 0.0Q;
        for (int i = 0; i < qdata->count; i++) {
            sum += qdata->data[i];
        }
        return sum;
    }
    // Function to calculate the average of __float128 numbers
    __float128 average_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to calculate average\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        return sum_qdata(qdata) / qdata->count;
    }
    // Function to calculate the variance of __float128 numbers
    __float128 variance_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to calculate variance\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        __float128 mean = average_qdata(qdata);
        __float128 variance = 0.0Q;
        for (int i = 0; i < qdata->count; i++) {
            variance += (qdata->data[i] - mean) * (qdata->data[i] - mean);
        }
        return variance / qdata->count;
    }
    // Function to calculate the standard deviation of __float128 numbers
    __float128 stddev_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to calculate standard deviation\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        return sqrtq(variance_qdata(qdata));
    }
    // Function to find the minimum value in __float128 numbers
    __float128 min_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to find minimum\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        __float128 min = qdata->data[0];
        for (int i = 1; i < qdata->count; i++) {
            if (qdata->data[i] < min) {
                min = qdata->data[i];
            }
        }
        return min;
    }
    // Function to find the maximum value in __float128 numbers
    __float128 max_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to find maximum\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        __float128 max = qdata->data[0];
        for (int i = 1; i < qdata->count; i++) {
            if (qdata->data[i] > max) {
                max = qdata->data[i];
            }
        }
        return max;
    }
    // Function to find the median of __float128 numbers
    __float128 median_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to find median\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        // Sort the data
        qsort(qdata->data, qdata->count, sizeof(__float128), compare_float128); 
        if (qdata->count % 2 == 0) {
            // If even, return the average of the two middle values
            return (qdata->data[qdata->count / 2 - 1] + qdata->data[qdata->count / 2]) / 2.0Q;
        } else {
            // If odd, return the middle value
            return qdata->data[qdata->count / 2];
        }
    }
    // Function to find the mode of __float128 numbers
    __float128 mode_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to find mode\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        // Create a frequency map
        int freq[MAX_DATA] = {0};
        for (int i = 0; i < qdata->count; i++) {
            freq[(int)qdata->data[i]]++;
        }
        // Find the mode
        int max_freq = 0;
        __float128 mode = qdata->data[0];
        for (int i = 0; i < qdata->count; i++) {
            if (freq[(int)qdata->data[i]] > max_freq) {
                max_freq = freq[(int)qdata->data[i]];
                mode = qdata->data[i];
            }
        }
        return mode;
    }
    // Function to find the range of __float128 numbers
    __float128 range_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to find range\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        return max_qdata(qdata) - min_qdata(qdata);
    }
    // Function to find the sum of squares of __float128 numbers
    __float128 sumsq_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to calculate sum of squares\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        __float128 sumsq = 0.0Q;
        for (int i = 0; i < qdata->count; i++) {
            sumsq += qdata->data[i] * qdata->data[i];
        }
        return sumsq;
    }
    // Function to find the sum of cubes of __float128 numbers
    __float128 sumcubes_qdata(QData *qdata) {
        if (qdata->count == 0) {
            fprintf(stderr, "No data to calculate sum of cubes\n");
            free_qdata(qdata);
            return EXIT_FAILURE;
        }
        __float128 sumcubes = 0.0Q;
        for (int i = 0; i < qdata->count; i++) {
            sumcubes += qdata->data[i] * qdata->data[i] * qdata->data[i];
        }
        return sumcubes;
    }
    // Function to compare two __float128 numbers for qsort
    int compare_float128(const void *a, const void *b) {
        __float128 val1 = *(const __float128 *)a;
        __float128 val2 = *(const __float128 *)b;
        if (val1 < val2) {
            return -1;
        } else if (val1 > val2) {
            return 1;
        } else {
            return 0;
        }
    }
    // Function to print __float128 numbers
    void print_qdata(QData *qdata) {
        for (int i = 0; i < qdata->count; i++) {
            printf("%.*Qf\n", MAX_BUF, qdata->data[i]);
        }
    }
    // Function to print statistics
    void print_qdata_stats(QData *qdata) {
        printf("Count: %llu\n", qdata->count);
        print_qdata("Sum: %.*Qf\n", MAX_BUF, sum_qdata(qdata));
        print_qdata("Average: %.*Qf\n", MAX_BUF, average_qdata(qdata));
        print_qdata("Variance: %.*Qf\n", MAX_BUF, variance_qdata(qdata));
        print_qdata("Standard Deviation: %.*Qf\n", MAX_BUF, stddev_qdata(qdata));
        print_qdata("Minimum: %.*Qf\n", MAX_BUF, min_qdata(qdata));
        print_qdata("Maximum: %.*Qf\n", MAX_BUF, max_qdata(qdata));
        print_qdata("Median: %.*Qf\n", MAX_BUF, median_qdata(qdata));
        print_qdata("Mode: %.*Qf\n", MAX_BUF, mode_qdata(qdata));
        print_qdata("Range: %.*Qf\n", MAX_BUF, range_qdata(qdata));
        print_qdata("Sum of Squares: %.*Qf\n", MAX_BUF, sumsq_qdata(qdata));
        print_qdata("Sum of Cubes: %.*Qf\n", MAX_BUF, sumcubes_qdata(qdata));

    }
