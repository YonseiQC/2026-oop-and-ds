int max(const int* a, int length) {
    int m = a[0];
    // m equals the maximum value in a[0:1]
    for (int i = 1; i < length; i++) {
        // Invariant: m equals the maximum value in a[0:i]
        if (m < a[i]) {
            m = a[i];
		}
        // m equals the maximum value in a[0:i+1]
    }
    // m equals the maximum value in a[0:i], and i==length
    return m;
}
