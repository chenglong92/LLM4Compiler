// Optimized code(id = 70): 

void subsample_ind_and_labels_CPU(int* d_ind_sub, const int* d_ind, unsigned int* d_label_sub, const unsigned int* d_label, int n_out, float inv_sub_factor) {
            for (unsigned int ind_out = 0; ind_out < n_out; ++ind_out) {
                int ind_in = static_cast<int>(floorf(static_cast<float>(ind_out) * inv_sub_factor));
                d_ind_sub[ind_out] = d_ind[ind_in];
                d_label_sub[ind_out] = d_label[ind_in];
            }
        }