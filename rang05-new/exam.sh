#!/bin/bash

# Colors for better visualization
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'

# Working directories
EXAM_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$EXAM_DIR")"
PROGRESS_DIR="$EXAM_DIR/exam_progress"
RENDU_DIR="$PROJECT_ROOT/rendu"

# Create necessary directories
mkdir -p "$PROGRESS_DIR"
mkdir -p "$RENDU_DIR"

# Files to store completed exercises per level
LEVEL1_DONE="$PROGRESS_DIR/level1_done.txt"
LEVEL2_DONE="$PROGRESS_DIR/level2_done.txt"

# Create files if missing
touch "$LEVEL1_DONE" "$LEVEL2_DONE"

# Validate exercise function
validate_exercise() {
    local level=$1
    local exercise=$2
    local exercise_dir="$EXAM_DIR/level-${level}/${exercise}"
    local grademe_dir="$exercise_dir/grademe"
    local student_dir="$RENDU_DIR/${exercise}"
    local student_file="${student_dir}/${exercise}.c"
    local test_script="$grademe_dir/test.sh"
    local student_cpp_file="${student_dir}/${exercise}.cpp"

    # Check that tests exist
    if [ ! -d "$grademe_dir" ]; then
        echo -e "${RED}Error: Tests not found for $exercise${NC}"
        echo -e "${YELLOW}Creating directory: $grademe_dir${NC}"
        mkdir -p "$grademe_dir" || {
            echo -e "${RED}Error: Could not create test directory${NC}"
            return 1
        }

        # Create placeholder test file
        echo "echo 'Tests have not been created yet'" > "$grademe_dir/test.sh"
        chmod +x "$grademe_dir/test.sh"
    fi

    # Check that student directory exists
    if [ ! -d "$student_dir" ]; then
        echo -e "${RED}Error: Student directory not found: $student_dir${NC}"
        echo -e "${YELLOW}Create it: mkdir $student_dir${NC}"
        return 1
    fi

    # Check for .c or .cpp file
    if [ ! -f "$student_file" ] && [ ! -f "$student_cpp_file" ]; then
        echo -e "${RED}Error: Neither $student_file nor $student_cpp_file exists${NC}"
        return 1
    fi

    echo -e "${BLUE}Running tests for $exercise...${NC}"
    cd "$grademe_dir"
    ./test.sh
    local test_result=$?
    cd "$EXAM_DIR"

    if [ $test_result -eq 0 ]; then
        echo -e "${GREEN}✅ Test passed for $exercise${NC}"
        return 0
    else
        echo -e "${RED}❌ Test failed for $exercise${NC}"
        return 1
    fi
}

# Count total exercises per level
count_total_exercises() {
    local level=$1
    find "$EXAM_DIR/level-${level}" -maxdepth 1 -mindepth 1 -type d | wc -l
}

# Get available exercises (not completed)
get_available_exercises() {
    local level=$1
    local done_file="$PROGRESS_DIR/level${level}_done.txt"
    local exercises=()

    for dir in level-${level}/*/; do
        if [ -d "$dir" ]; then
            dirname=$(basename "$dir")
            if ! grep -q "^$dirname$" "$done_file" 2>/dev/null; then
                exercises+=("$dirname")
            fi
        fi
    done

    echo "${exercises[@]}"
}

# Show progress
show_progress() {
    echo -e "\n${BLUE}=== CURRENT PROGRESS ===${NC}"
    for i in {1..2}; do
        local total=$(count_total_exercises $i)
        local done_file="$PROGRESS_DIR/level${i}_done.txt"
        local completed=$(sort "$done_file" 2>/dev/null | uniq | wc -l)
        echo -e "${GREEN}Level $i: $completed/$total completed${NC}"
    done
    echo
}

# Remove duplicates in progress files
clean_progress_files() {
    for i in {1..2}; do
        local done_file="$PROGRESS_DIR/level${i}_done.txt"
        if [ -f "$done_file" ]; then
            sort "$done_file" | uniq > "${done_file}.tmp"
            mv "${done_file}.tmp" "$done_file"
        fi
    done
}

# Select a random exercise
select_random_exercise() {
    local level=$1
    local exercises=($(get_available_exercises $level))
    local count=${#exercises[@]}

    if [ $count -eq 0 ]; then
        echo -e "${YELLOW}All exercises in level $level are completed!${NC}"
        return 1
    fi

    local random_index=$((RANDOM % count))
    echo "${exercises[$random_index]}"
}

# List exercises for a level
list_level_exercises() {
    local level=$1
    local exercises=()
    local index=1

    echo -e "\n${BLUE}=== LEVEL $level EXERCISES ===${NC}"

    for dir in level-${level}/*/; do
        if [ -d "$dir" ]; then
            dirname=$(basename "$dir")
            exercises+=("$dirname")
            echo "$index) $dirname"
            ((index++))
        fi
    done

    echo -e "\n${YELLOW}Select exercise (1-$((index-1))) or 0 to go back:${NC}"
    read -r selection

    if [[ "$selection" =~ ^[0-9]+$ ]] && [ "$selection" -gt 0 ] && [ "$selection" -lt "$index" ]; then
        practice_single_exercise "$level" "${exercises[$((selection-1))]}"
    elif [ "$selection" != "0" ]; then
        echo -e "${RED}Invalid selection${NC}"
        read -p "Press Enter to continue..."
    fi
}

# Level selection menu
select_level() {
    while true; do
        clear
        echo -e "${BLUE}=== SELECT LEVEL ===${NC}"
        echo "1. Level 1"
        echo "2. Level 2"
        echo "0. Back"

        read -r level_choice

        case $level_choice in
            [1-2]) list_level_exercises "$level_choice" ;;
            0) return ;;
            *) 
                echo -e "${RED}Invalid option${NC}"
                read -p "Press Enter to continue..."
                ;;
        esac
    done
}

# Practice a specific exercise
practice_single_exercise() {
    local level=$1
    local exercise=$2

    show_subject $level "$exercise"

    while true; do
        echo -e "\n${YELLOW}Options:${NC}"
        echo "1. Validate exercise"
        echo "2. Mark as completed without validating"
        echo "3. Leave as pending"
        echo "4. Exit"
        read -r option

        case $option in
            1)
                if validate_exercise $level "$exercise"; then
                    mark_as_completed $level "$exercise"
                    echo -e "${GREEN}Exercise $exercise marked as completed${NC}"
                    read -p "Press Enter..."
                    return
                else
                    echo -e "${RED}Validation failed${NC}"
                    read -p "Press Enter..."
                fi
                ;;
            2)
                mark_as_completed $level "$exercise"
                echo -e "${GREEN}Exercise $exercise marked as completed${NC}"
                read -p "Press Enter..."
                return
                ;;
            3)
                echo -e "${YELLOW}Exercise left pending${NC}"
                read -p "Press Enter..."
                return
                ;;
            4)
                return
                ;;
            *)
                echo -e "${RED}Invalid option${NC}"
                ;;
        esac
    done
}

# Show subject file
show_subject() {
    local level=$1
    local exercise=$2
    local subject_file="$EXAM_DIR/level-${level}/${exercise}/subject.txt"

    clear
    echo -e "${BLUE}=== EXAM RANK 05 - LEVEL $level ===${NC}"
    echo -e "${CYAN}Exercise: $exercise${NC}"
    echo ""

    if [ -f "$subject_file" ]; then
        cat "$subject_file"
    else
        echo -e "${RED}Error: subject file not found${NC}"
        echo "Searching: $subject_file"
    fi

    echo ""
    echo -e "${YELLOW}Working directory: $PROJECT_ROOT/rendu/${exercise}/${NC}"
    echo -e "${YELLOW}Expected file: ${exercise}.cpp (or ${exercise}.c)${NC}"
    echo ""
}

# Mark exercise as completed
mark_as_completed() {
    local level=$1
    local exercise=$2
    local done_file="$PROGRESS_DIR/level${level}_done.txt"

    echo "$exercise" >> "$done_file"
    clean_progress_files
}

# Random practice mode
practice_random() {
    while true; do
        clear
        echo -e "${BLUE}=== PRACTICE MODE - EXAM RANK 05 ===${NC}"
        show_progress

        echo -e "${YELLOW}Select level for random exercise:${NC}"
        echo "1. Level 1"
        echo "2. Level 2"
        echo "0. Back"

        read -r level_choice

        case $level_choice in
            [1-2])
                exercise=$(select_random_exercise $level_choice)
                if [ $? -eq 0 ] && [ -n "$exercise" ]; then
                    echo -e "${GREEN}Random exercise selected: $exercise${NC}"
                    read -p "Press Enter..."
                    practice_single_exercise $level_choice "$exercise"
                else
                    read -p "Press Enter..."
                fi
                ;;
            0)
                return
                ;;
            *)
                echo -e "${RED}Invalid option${NC}"
                read -p "Press Enter..."
                ;;
        esac
    done
}

# Show statistics
show_stats() {
    clear
    echo -e "${BLUE}=== STATISTICS - EXAM RANK 05 ===${NC}"
    show_progress

    echo -e "${CYAN}=== COMPLETED EXERCISES ===${NC}"
    for i in {1..2}; do
        local done_file="$PROGRESS_DIR/level${i}_done.txt"
        echo -e "\n${GREEN}Level $i:${NC}"
        if [ -f "$done_file" ] && [ -s "$done_file" ]; then
            sort "$done_file" | uniq | nl
        else
            echo "  No completed exercises"
        fi
    done

    echo ""
    read -p "Press Enter..."
}

# Reset progress
reset_progress() {
    clear
    echo -e "${BLUE}=== RESET PROGRESS - EXAM RANK 05 ===${NC}"
    echo -e "${RED}Are you sure you want to reset all progress? (y/n)${NC}"
    read -r confirm

    if [[ "$confirm" =~ ^[Yy]$ ]]; then
        > "$LEVEL1_DONE"
        > "$LEVEL2_DONE"

        # Clean rendu directory
        for dir in level-{1,2}/*/; do
            if [ -d "$dir" ]; then
                exercise=$(basename "$dir")
                rm -rf "$RENDU_DIR/$exercise"
            fi
        done

        echo -e "${GREEN}Progress reset and rendu directory cleaned${NC}"
    else
        echo -e "${YELLOW}Operation cancelled${NC}"
    fi

    read -p "Press Enter..."
}

# Main menu
main_menu() {
    clean_progress_files

    while true; do
        clear
        echo -e "${BLUE}╔══════════════════════════════════════════════════════╗${NC}"
        echo -e "${BLUE}║                 EXAM RANK 05 - PRACTICE              ║${NC}"
        echo -e "${BLUE}╚══════════════════════════════════════════════════════╝${NC}"
        echo ""

        show_progress

        echo -e "${YELLOW}=== MAIN MENU ===${NC}"
        echo "1. 🎲 Random exercise by level"
        echo "2. 📋 Choose exercise manually"
        echo "3. 📊 View statistics"
        echo "4. 🔄 Reset progress"
        echo "5. 🚪 Exit"
        echo ""

        read -p "Select an option: " choice

        case $choice in
            1) practice_random ;;
            2) select_level ;;
            3) show_stats ;;
            4) reset_progress ;;
            5)
                echo -e "${GREEN}Goodbye!${NC}"
                exit 0
                ;;
            *)
                echo -e "${RED}Invalid option${NC}"
                read -p "Press Enter..."
                ;;
        esac
    done
}

# Check working directory
if [ ! -d "level-1" ] && [ ! -d "level-2" ]; then
    echo -e "${RED}Error: Level directories not found${NC}"
    echo -e "${YELLOW}Make sure you run this script from the 05 directory${NC}"
    exit 1
fi

# Start program
main_menu
