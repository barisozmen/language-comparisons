#!/bin/bash

# ===== Language Wars Benchmark Script =====
# This script benchmarks implementations of algorithms in different programming languages

set -e

# ===== Configuration =====
WARMUP_RUNS=3              # Number of warmup runs for JIT compilers
BENCHMARK_RUNS=10          # Number of benchmark runs for statistical significance
OUTPUT_DIR="reports"       # Directory for benchmark results
COMPILE_DIR="build"        # Directory for compiled executables
TIMEOUT_SECONDS=30         # Maximum execution time before timeout

# ===== Color definitions =====
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# ===== Function to display usage =====
function show_usage {
    echo -e "${BLUE}Usage:${NC} $0 [OPTIONS] <algorithm_directory>"
    echo
    echo "OPTIONS:"
    echo "  -h, --help                 Show this help message"
    echo "  -l, --language LANG        Benchmark only the specified language"
    echo "  -r, --runs NUMBER          Set number of benchmark runs (default: $BENCHMARK_RUNS)"
    echo "  -w, --warmup NUMBER        Set number of warmup runs (default: $WARMUP_RUNS)"
    echo "  -v, --verbose              Enable verbose output"
    echo "  -s, --skip-compile         Skip compilation step"
    echo "  -o, --output-dir DIR       Set output directory (default: $OUTPUT_DIR)"
    echo
    echo "EXAMPLES:"
    echo "  $0 algorithms/fibonacci"
    echo "  $0 --language python algorithms/merge_sort"
    echo "  $0 --runs 20 --warmup 5 algorithms/prime_sieve"
    exit 1
}

# ===== Function to check if a command exists =====
function command_exists {
    command -v "$1" &> /dev/null
}

# ===== Function to create directories if they don't exist =====
function ensure_dir {
    if [ ! -d "$1" ]; then
        mkdir -p "$1"
        echo -e "${GREEN}Created directory:${NC} $1"
    fi
}

# ===== Function to compile a source file =====
function compile_source {
    local lang=$1
    local source_file=$2
    local algorithm_name=$3
    local output_file="${COMPILE_DIR}/${algorithm_name}_${lang}"

    # Ensure the compile directory exists
    ensure_dir "$COMPILE_DIR"

    echo -e "${CYAN}Compiling${NC} $source_file ${CYAN}to${NC} $output_file"

    case $lang in
        c)
            if command_exists gcc; then
                gcc -O3 -march=native -flto -Wall -Wextra "$source_file" -o "$output_file" -lm
            else
                echo -e "${RED}Error:${NC} gcc not found. Please install gcc to compile C programs."
                return 1
            fi
            ;;
        cpp)
            if command_exists g++; then
                g++ -std=c++17 -O3 -march=native -flto -Wall -Wextra "$source_file" -o "$output_file" -lm
            else
                echo -e "${RED}Error:${NC} g++ not found. Please install g++ to compile C++ programs."
                return 1
            fi
            ;;
        rust)
            if command_exists rustc; then
                rustc -C opt-level=3 -C target-cpu=native "$source_file" -o "$output_file"
            else
                echo -e "${RED}Error:${NC} rustc not found. Please install Rust to compile Rust programs."
                return 1
            fi
            ;;
        *)
            echo -e "${YELLOW}Warning:${NC} No compilation needed for $lang"
            ;;
    esac
}

# ===== Function to run a benchmark =====
function run_benchmark {
    local lang=$1
    local source_file=$2
    local algorithm_name=$3
    local input_args=${4:-""}
    local time_result="0"
    local mem_result="0"
    local exit_status=0
    local output_file="${COMPILE_DIR}/${algorithm_name}_${lang}"

    # Prepare command to run based on language
    local cmd=""
    case $lang in
        c|cpp|rust)
            if [ -f "$output_file" ]; then
                cmd="$output_file $input_args"
            else
                echo -e "${RED}Error:${NC} Compiled executable not found: $output_file"
                return 1
            fi
            ;;
        python)
            if command_exists python3; then
                cmd="python3 $source_file $input_args"
            elif command_exists python; then
                cmd="python $source_file $input_args"
            else
                echo -e "${RED}Error:${NC} Python not found. Please install Python."
                return 1
            fi
            ;;
        js|javascript)
            if command_exists node; then
                cmd="node $source_file $input_args"
            else
                echo -e "${RED}Error:${NC} Node.js not found. Please install Node.js."
                return 1
            fi
            ;;
        scm|scheme)
            if command_exists guile; then
                cmd="guile $source_file $input_args"
            elif command_exists racket; then
                cmd="racket -f $source_file $input_args"
            else
                echo -e "${RED}Error:${NC} Scheme interpreter not found. Please install Guile or Racket."
                return 1
            fi
            ;;
        *)
            echo -e "${RED}Error:${NC} Unsupported language: $lang"
            return 1
            ;;
    esac

    # Run the benchmark with /usr/bin/time for memory usage
    if command_exists /usr/bin/time; then
        # Create a temporary file for the time output
        local time_output="/tmp/benchmark_time_$$.txt"
        
        # Run the command with timeout and capture time output
        if timeout $TIMEOUT_SECONDS /usr/bin/time -f "%e %M" $cmd > /dev/null 2> "$time_output"; then
            # Read time and memory from the time output file
            local time_mem=$(cat "$time_output")
            time_result=$(echo "$time_mem" | awk '{print $1}')
            mem_result=$(echo "$time_mem" | awk '{print $2}')
            rm -f "$time_output"
        else
            exit_status=$?
            if [ $exit_status -eq 124 ]; then
                echo -e "${RED}Error:${NC} Command timed out after $TIMEOUT_SECONDS seconds"
                time_result="TIMEOUT"
                mem_result="TIMEOUT"
            else
                echo -e "${RED}Error:${NC} Command failed with exit code $exit_status"
                time_result="ERROR"
                mem_result="ERROR"
            fi
            rm -f "$time_output"
        fi
    else
        # Fallback to simple time measurement if /usr/bin/time is not available
        echo -e "${YELLOW}Warning:${NC} /usr/bin/time not found. Using simple time measurement without memory usage."
        local start_time=$(date +%s.%N)
        if timeout $TIMEOUT_SECONDS $cmd > /dev/null; then
            local end_time=$(date +%s.%N)
            time_result=$(echo "$end_time - $start_time" | bc)
            mem_result="N/A"
        else
            exit_status=$?
            if [ $exit_status -eq 124 ]; then
                echo -e "${RED}Error:${NC} Command timed out after $TIMEOUT_SECONDS seconds"
                time_result="TIMEOUT"
                mem_result="TIMEOUT"
            else
                echo -e "${RED}Error:${NC} Command failed with exit code $exit_status"
                time_result="ERROR"
                mem_result="ERROR"
            fi
        fi
    fi

    # Sanitize the output to ensure it's safe for parsing
    if [[ "$time_result" == "ERROR" || "$time_result" == "TIMEOUT" ]]; then
        echo "$time_result $mem_result"
    else
        # Make sure we're returning valid numeric values
        echo "$time_result $mem_result"
    fi
}

# ===== Parse command-line arguments =====
ALGORITHM_DIR=""
SELECTED_LANG=""
VERBOSE=false
SKIP_COMPILE=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            ;;
        -l|--language)
            SELECTED_LANG="$2"
            shift 2
            ;;
        -r|--runs)
            BENCHMARK_RUNS="$2"
            shift 2
            ;;
        -w|--warmup)
            WARMUP_RUNS="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -s|--skip-compile)
            SKIP_COMPILE=true
            shift
            ;;
        -o|--output-dir)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        *)
            if [[ -z "$ALGORITHM_DIR" ]]; then
                ALGORITHM_DIR="$1"
                shift
            else
                echo -e "${RED}Error:${NC} Unknown argument: $1"
                show_usage
            fi
            ;;
    esac
done

# ===== Validate arguments =====
if [[ -z "$ALGORITHM_DIR" ]]; then
    echo -e "${RED}Error:${NC} Algorithm directory is required"
    show_usage
fi

if [[ ! -d "$ALGORITHM_DIR" ]]; then
    echo -e "${RED}Error:${NC} Algorithm directory does not exist: $ALGORITHM_DIR"
    exit 1
fi

# Extract algorithm name from the directory path
ALGORITHM_NAME=$(basename "$ALGORITHM_DIR")
echo -e "${GREEN}Benchmarking algorithm:${NC} $ALGORITHM_NAME"

# ===== Create necessary directories =====
ensure_dir "$OUTPUT_DIR"
ensure_dir "$COMPILE_DIR"

# ===== Define results file =====
RESULTS_FILE="${OUTPUT_DIR}/${ALGORITHM_NAME}_benchmark.csv"
# Ensure results file exists
if [ ! -f "$RESULTS_FILE" ]; then
    echo "language,file,run,time_seconds,memory_kb" > "$RESULTS_FILE"
    echo -e "${GREEN}Created results file:${NC} $RESULTS_FILE"
else
    echo -e "${GREEN}Results will be appended to:${NC} $RESULTS_FILE"
fi

# ===== Find implementation files =====
cd "$ALGORITHM_DIR"
echo -e "${BLUE}Searching for implementations in:${NC} $(pwd)"

# Replace the associative array with simple arrays
LANG_NAMES=("c" "cpp" "python" "js" "rust" "scheme")
LANG_EXTENSIONS=(".c" ".cpp" ".py" ".js" ".rs" ".scm")

# Process each implementation file
for i in "${!LANG_NAMES[@]}"; do
    lang="${LANG_NAMES[$i]}"
    ext="${LANG_EXTENSIONS[$i]}"
    
    # Skip if a specific language was requested and this isn't it
    if [[ -n "$SELECTED_LANG" && "$SELECTED_LANG" != "$lang" ]]; then
        continue
    fi
    
    # Find implementation files for this language
    files=$(find . -maxdepth 1 -name "*$ext" -not -name "test_*" -not -name "*_test*")
    
    for file in $files; do
        base_file=$(basename "$file")
        echo -e "${MAGENTA}Found implementation:${NC} $lang - $base_file"
        
        # Compile if necessary
        if [[ "$SKIP_COMPILE" = false ]]; then
            case $lang in
                c|cpp|rust)
                    compile_source "$lang" "$file" "$ALGORITHM_NAME" || continue
                    ;;
                *)
                    # No compilation needed
                    ;;
            esac
        fi
        
        echo -e "${YELLOW}Running warmup...${NC}"
        # Perform warmup runs
        for ((i=1; i<=$WARMUP_RUNS; i++)); do
            if $VERBOSE; then
                echo -e "${BLUE}Warmup run $i${NC}"
            fi
            run_benchmark "$lang" "$file" "$ALGORITHM_NAME" > /dev/null
        done
        
        echo -e "${GREEN}Running benchmark...${NC}"
        # Perform actual benchmark runs
        total_time=0
        total_mem=0
        successful_runs=0
        
        for ((i=1; i<=$BENCHMARK_RUNS; i++)); do
            echo -ne "${CYAN}Run $i/${BENCHMARK_RUNS}${NC} "
            result=$(run_benchmark "$lang" "$file" "$ALGORITHM_NAME")
            if [[ "$result" == *"ERROR"* ]]; then
                time_result="ERROR"
                mem_result="ERROR"
            elif [[ "$result" == *"TIMEOUT"* ]]; then
                time_result="TIMEOUT"
                mem_result="TIMEOUT"
            else
                time_result=$(echo "$result" | awk '{print $1}')
                mem_result=$(echo "$result" | awk '{print $2}')
            fi
            
            if [[ "$time_result" != "ERROR" && "$time_result" != "TIMEOUT" ]]; then
                echo -e "${GREEN}✓${NC} ${time_result}s, ${mem_result}KB"
                total_time=$(echo "$total_time + $time_result" | bc)
                if [[ "$mem_result" != "N/A" ]]; then
                    total_mem=$(echo "$total_mem + $mem_result" | bc)
                fi
                successful_runs=$((successful_runs + 1))
                
                # Write result to CSV
                ensure_dir "$(dirname "../$RESULTS_FILE")"
                echo "$lang,$base_file,$i,$time_result,$mem_result" >> "../$RESULTS_FILE"
            else
                echo -e "${RED}✗${NC} $time_result"
                # Write error to CSV
                ensure_dir "$(dirname "../$RESULTS_FILE")"
                echo "$lang,$base_file,$i,$time_result,$mem_result" >> "../$RESULTS_FILE"
            fi
        done
        
        # Calculate and display averages if there were successful runs
        if [[ $successful_runs -gt 0 ]]; then
            avg_time=$(echo "scale=6; $total_time / $successful_runs" | bc)
            if [[ "$mem_result" != "N/A" ]]; then
                avg_mem=$(echo "scale=0; $total_mem / $successful_runs" | bc)
                echo -e "${BLUE}Average:${NC} ${avg_time}s, ${avg_mem}KB over $successful_runs runs"
            else
                echo -e "${BLUE}Average:${NC} ${avg_time}s over $successful_runs runs"
            fi
        else
            echo -e "${RED}No successful runs${NC}"
        fi
        
        echo "----------------------------------------"
    done
done

cd - > /dev/null

echo -e "${GREEN}Benchmark complete!${NC} Results saved to $RESULTS_FILE"
echo -e "${YELLOW}Note:${NC} Run generate_report.py to create a formatted report from these results" 


# ===== Example usage =====
# Benchmark all fibonacci implementations
# ./benchmark.sh algorithms/fibonacci

# # Benchmark only Python implementation
# ./benchmark.sh --language python algorithms/fibonacci

# # Customize number of runs and warmup iterations
# ./benchmark.sh --runs 20 --warmup 5 algorithms/merge_sort

# # Skip compilation step (useful during development)
# ./benchmark.sh --skip-compile algorithms/prime_sieve