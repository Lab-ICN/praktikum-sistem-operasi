#!/usr/bin/env bash

set -euo pipefail

module_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
build_dir="$(mktemp -d)"
trap 'rm -rf "$build_dir"' EXIT

required_sources=(
    Loop_NIM.c
    fork_NIM.c
    threadsatu_NIM.c
    threaddua_NIM.c
    singlethread_NIM.c
    threadtiga_NIM.c
)

for source in "${required_sources[@]}"; do
    if [[ ! -f "$module_dir/$source" ]]; then
        printf 'FAIL: berkas wajib tidak ditemukan: %s\n' "$source" >&2
        exit 1
    fi
done

common_flags=(-std=c11 -Wall -Wextra -Wpedantic -Wstrict-prototypes -Werror -O2)

gcc "${common_flags[@]}" "$module_dir/Loop_NIM.c" -o "$build_dir/loop"
gcc "${common_flags[@]}" "$module_dir/fork_NIM.c" -o "$build_dir/fork_process"
gcc "${common_flags[@]}" -pthread "$module_dir/threadsatu_NIM.c" -o "$build_dir/thread_satu"
gcc "${common_flags[@]}" -pthread "$module_dir/threaddua_NIM.c" -o "$build_dir/thread_dua"
gcc "${common_flags[@]}" "$module_dir/singlethread_NIM.c" -o "$build_dir/single_thread"
gcc "${common_flags[@]}" -pthread "$module_dir/threadtiga_NIM.c" -o "$build_dir/thread_tiga"

fork_output="$($build_dir/fork_process)"
grep -q 'child process' <<<"$fork_output"
grep -q 'parent process' <<<"$fork_output"

single_output="$($build_dir/single_thread -a 32 -i 200 -t 0 2>&1)"
grep -q 'Values are still consistent' <<<"$single_output"

multi_output="$($build_dir/thread_tiga -a 32 -i 200 -t 0 -n 2 --safe 2>&1)"
grep -q 'Values are still consistent' <<<"$multi_output"

printf 'PASS: 6 berkas lengkap, seluruhnya berhasil dikompilasi, dan uji perilaku lulus.\n'
