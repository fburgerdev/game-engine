#include "file.hpp"
#include <filesystem>
#include <iostream>

namespace intern {
    File::File(const Filepath& filepath) {
        open(filepath);
    }

    bool File::open(const Filepath& filepath) {
        m_stream.open(filepath);
        return m_stream.is_open();
    }
    void File::close() {
        m_stream.close();
    }
    bool File::is_open() {
        return m_stream.is_open();
    }

    void File::set_cursor(u32 pos) {
        m_stream.seekg(pos);
    }
    void File::set_cursor(u32 line, u32 column) {
        m_stream.seekg(0);
        u32 curr_line = 0;
        while (!reached_end() && curr_line < line) {
            read_line();
            ++curr_line;
        }
        m_stream.seekg(m_stream.tellg() + std::streamoff(column));
    }
    bool File::reached_end() {
        return m_stream.eof();
    }

    void File::write_char(char ch) {
        m_stream.put(ch);
    }
    char File::read_char() {
        return (char)m_stream.get();
    }

    void File::write_line(const string& str) {
        m_stream.write(str.c_str(), str.size());
        m_stream.put('\n');
    }
    string File::read_line() {
        string line;
        std::getline(m_stream, line);
        return line;
    }

    string File::extract_all() {
        set_cursor(0);
        string out;
        while (!reached_end()) {
            out += read_line() + "\n";
        }
        return out;
    }

    void File::write_i32(i32 arg) {
        return write_struct<i32>(arg);
    }
    i32 File::read_i32() {
        return read_struct<i32>();
    }
    void File::write_f32(f32 arg) {
        return write_struct<f32>(arg);
    }
    f32 File::read_f32() {
        return read_struct<f32>();
    }
    void File::write_f64(f64 arg) {
        return write_struct<f64>(arg);
    }
    f64 File::read_f64() {
        return read_struct<f64>();
    }

    Directory get_directory(const Filepath& filepath) {
        adress found = filepath.find_last_of('/');
        if (found == filepath.npos) {
            return "";
        }
        else {
            return filepath.substr(0, found);
        }
    }
    Filename get_filename(const Filepath& filepath) {
        return filepath.substr(filepath.find_last_of('\\') + 1);
    }
    Extension get_extension(const Filepath& filepath) {
        const Filename filename = get_filename(filepath);
        adress found = filename.find_first_of('.');
        if (found == filename.npos) {
            return "";
        }
        else {
            return filename.substr(found + 1);
        }
    }

    List<Filepath> extract_files(const Directory& directory) {
        List<Filepath> files;
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (!std::filesystem::is_directory(entry.path())) {
                files.push_back(entry.path().string());
            }
        }
        return files;
    }
    List<Filepath> extract_files_recursive(const Directory& directory) {
        List<Filepath> files;
        Queue<Directory> queue({ directory });
        while (!queue.empty()) {
            Directory directory = queue.front();
            queue.pop();
            for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                if (std::filesystem::is_directory(entry.path())) {
                    queue.push(entry.path().string());
                }
                else {
                    files.push_back(entry.path().string());
                }
            }
        }
        return files;
    }
    List<Directory> extract_directories(const Directory& directory) {
        List<Directory> directories;
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (std::filesystem::is_directory(entry.path())) {
                directories.push_back(entry.path().string());
            }
        }
        return directories;
    }

    Filepath find_in_directory(const Filename& filename, const Directory& directory) {
        for (const Filepath& filepath : extract_files_recursive(directory)) {
            if (get_filename(filepath) == filename) {
                return filepath;
            }
        }
        return "";
    }
}