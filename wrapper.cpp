#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>
#include "input/genAnalysisLogic.h"
#include "input/genAnalysisLogic_emxAPI.h"

using namespace emscripten;

// Safely stub out OpenMP to prevent threading crashes
extern "C" {
    void omp_init_nest_lock(void*) {}
    void omp_destroy_nest_lock(void*) {}
    void omp_set_nest_lock(void*) {}
    void omp_unset_nest_lock(void*) {}
    int omp_get_num_threads() { return 1; }
    int omp_get_max_threads() { return 1; }
    int omp_get_thread_num() { return 0; }
}

// MATLAB's auto-generated initialization function
extern "C" void genAnalysisLogic_initialize();

val run_genAnalysisLogic(const val &x_js, double Fs) {
    // 1. Initialize MATLAB's FFT cache exactly ONCE to prevent leaks
    static bool is_initialized = false;
    if (!is_initialized) {
        genAnalysisLogic_initialize();
        is_initialized = true;
    }

    // 2. Read audio from JavaScript
    size_t x_len = x_js["length"].as<size_t>();
    std::vector<double> x_buf(x_len);
    if (x_len > 0) {
        val x_view = val(typed_memory_view(x_len, x_buf.data()));
        x_view.call<void>("set", x_js);
    }

    // 3. Allocate secure MATLAB input array
    int in_sz[2] = { 1, (int)x_len };
    emxArray_real_T *x = emxCreateND_real_T(2, in_sz);
    for(size_t i = 0; i < x_len; i++) x->data[i] = x_buf[i];

    // 4. Allocate blank MATLAB output arrays
    int out_sz[2] = { 0, 0 };
    emxArray_real_T *t = emxCreateND_real_T(2, out_sz);
    emxArray_real_T *freq = emxCreateND_real_T(2, out_sz);
    emxArray_real_T *fftMagnitude = emxCreateND_real_T(2, out_sz);
    emxArray_real_T *stftTime = emxCreateND_real_T(2, out_sz);
    emxArray_real_T *stftFreq = emxCreateND_real_T(2, out_sz);
    emxArray_real_T *stftMagnitude = emxCreateND_real_T(2, out_sz);

    // 5. Run the Analyzer
    genAnalysisLogic(x, Fs, t, freq, fftMagnitude, stftTime, stftFreq, stftMagnitude);

    // 6. Bundle results to send back to JavaScript
    val result = val::object();
    auto to_js = [](emxArray_real_T* arr) {
        int numels = 1;
        for (int i = 0; i < arr->numDimensions; ++i) numels *= arr->size[i];
        val view = val(typed_memory_view(numels, arr->data));
        return val::global("Float64Array").new_(view);
    };

    result.set("t", to_js(t));
    result.set("freq", to_js(freq));
    result.set("fftMagnitude", to_js(fftMagnitude));
    result.set("stftTime", to_js(stftTime));
    result.set("stftFreq", to_js(stftFreq));
    result.set("stftMagnitude", to_js(stftMagnitude));

    // 7. Vaporize the memory to guarantee 0 leaks
    emxDestroyArray_real_T(x);
    emxDestroyArray_real_T(t);
    emxDestroyArray_real_T(freq);
    emxDestroyArray_real_T(fftMagnitude);
    emxDestroyArray_real_T(stftTime);
    emxDestroyArray_real_T(stftFreq);
    emxDestroyArray_real_T(stftMagnitude);

    return result;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("genAnalysisLogic", &run_genAnalysisLogic);
}