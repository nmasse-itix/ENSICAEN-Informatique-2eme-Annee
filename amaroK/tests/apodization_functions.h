
/**
 * Compute and stores hanning window coefficients in the given array
 *
 * @param array		where coeffs are stored (must be window_width long)
 * @param window_width	the number of coef to compute
 */
void hanning(float * array, int window_width);

/**
 * Print coeffs from 2 hanning windows, the first with 8 coeffs, the second
 * with 19
 */
void test_hanning();
