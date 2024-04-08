#include "tasks.h"

namespace sr = std::ranges;

std::ostream &operator<<(std::ostream &os, const Student &student) {
    os << student.name;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Exam &exam) {
    os << exam.subject;
    return os;
}

Score calculate_score(Student student, Exam exam) {
    int math_diff = static_cast<int>(student.math_skill) * std::max(1, 100 - static_cast<int>(exam.math_difficulty));
    int coding_diff =
            static_cast<int>(student.coding_skill) * std::max(1, 100 - static_cast<int>(exam.coding_difficulty));

    int diff = math_diff + coding_diff;
    return diff / 50;
}

///Mozna obcas zbytecne nebo tak. Chtela jsem si hlavne pohrat s STL a vyuzit co nejvice veci,
///abych se s nema seznamila. Snad to nebude brano za chybu xd

std::vector<std::pair<Student, Score>> find_best_n_students(std::vector<Student> students, const Exam &exam, size_t n) {
    std::vector<std::pair<Student, int>> studentScores;
    std::vector<std::pair<Student, int>> bestStudents;

    sr::transform(students, std::back_inserter(studentScores),
                           [&exam](const Student &student) {
                               return std::make_pair(student, calculate_score(student, exam));
                           });

    sr::sort(studentScores, std::greater<>{}, [](const auto &pair) { return pair.second; });
    sr::copy(studentScores | std::views::take(n), std::back_inserter(bestStudents));

    return bestStudents;
}

size_t max_score_difference(const std::vector<Student> &students, const std::vector<Exam> &exams) {
    if (exams.empty() || students.empty())
        return 0;

    std::vector<int> maxDifferences;

    std::for_each(exams.begin(), exams.end(), [&](const Exam &exam) {
        std::vector<Score> examScores;

        std::transform(students.begin(), students.end(), std::back_inserter(examScores), [&](const Student &student) {
            return calculate_score(student, exam);
        });

        std::sort(examScores.begin(), examScores.end(), std::greater<>{});

        int maxDiff = 0;
        //Chtela jsem vyuzit std::adjacent_difference, ale hazelo mi to minusove hodnoty
        // ale tak jeden for, se neposerem
        for (size_t i = 1; i < examScores.size(); ++i) {
            int diff = examScores[i - 1] - examScores[i];
            maxDiff = std::max(maxDiff, diff);
        }

        maxDifferences.push_back(maxDiff);
    });

    return *std::max_element(maxDifferences.begin(), maxDifferences.end());
}

std::pair<std::unordered_set<Student>, std::unordered_set<Student>>
filter_students(const std::vector<Student> &students, const std::vector<Exam> &exams) {
    std::unordered_set<Student> passedAllExams;
    std::unordered_set<Student> passedAtLeastOneExam;

    sr::copy_if(students, std::inserter(passedAllExams, passedAllExams.end()), [&](const Student &student) {
        return sr::all_of(exams, [&](const Exam &exam) {
            return calculate_score(student, exam) >= 100;
        });
    });

    sr::copy_if(students, std::inserter(passedAtLeastOneExam, passedAtLeastOneExam.end()),
                         [&](const Student &student) {
                             return sr::any_of(exams, [&](const Exam &exam) {
                                 return calculate_score(student, exam) >= 100;
                             });
                         });

    return {passedAllExams, passedAtLeastOneExam};
}

std::unordered_map<Subject, std::vector<std::pair<Student, Score>>>
get_leaderboard_of_each_subject(const std::vector<Student> &students, const std::vector<Exam> &exams) {
    std::unordered_map<Subject, std::unordered_map<Student, Score>> subjectScores;

    sr::for_each(exams, [&](const Exam &exam) {
        sr::for_each(students, [&](const Student &student) {
            subjectScores[exam.subject][student] += calculate_score(student, exam);
        });
    });

    std::unordered_map<Subject, std::vector<std::pair<Student, Score>>> leaderboard;

    sr::for_each(subjectScores, [&](const auto &subjectScore) {
        const auto &subject = subjectScore.first;
        const auto &studentsScores = subjectScore.second;

        std::vector<std::pair<Student, Score>> sortedStudents(studentsScores.begin(), studentsScores.end());
        sr::sort(sortedStudents, [](const auto &a, const auto &b) {
            return a.second != b.second ? a.second > b.second : a.first.name < b.first.name;
        });

        leaderboard[subject] = std::move(sortedStudents);
    });

    return leaderboard;
}
