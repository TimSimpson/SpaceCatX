int error_count = 0;

template<typename t>
void assert(const t & condition) {
    if (!condition) {
        error_count += 1;
    }
}

int main() {
    int answer = 2 + 3;
    assert(4 == answer);

    return error_count;
}
