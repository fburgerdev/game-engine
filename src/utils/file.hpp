#pragma once
#include "common.hpp"
#include <fstream>

namespace intern {
    using Filename = string;
    using Extension = string;
    using Filepath = string;
    using Directory = string;

    class File {
    public:
        File() = default;
        File(const Filepath& filepath);

        bool open(const Filepath& filepath);
        void close();
        bool is_open();

        void set_cursor(u32 pos);
        void set_cursor(u32 line, u32 column);
        bool reached_end();
        
        void write_char(char ch);
        char read_char();

        void write_line(const string& str);
        string read_line();
        string extract_all();
        
        template<typename T>
        void write_struct(const T& arg) {
            m_stream.write((char*)&arg, sizeof(T));
        }
        template<typename T>
        T read_struct() {
            T out;
            m_stream.read((char*)&out, sizeof(T));
            return out;
        }

        void write_i32(i32 arg);
        i32 read_i32();
        void write_f32(f32 arg);
        f32 read_f32();
        void write_f64(f64 arg);
        f64 read_f64();
    private:
        std::fstream m_stream;
    };

    template<typename T>
    void save_struct(const T& arg, const Filepath& filepath) {
        File file(filepath);
        file.write_struct(arg);
    }
    template<typename T>
    T load_struct(const Filepath& filepath) {
        File file(filepath);
        return file.read_struct<T>();
    }

    // filepath utils
    Directory get_directory(const Filepath& filepath);
    Filename get_filename(const Filepath& filepath);
    Extension get_extension(const Filepath& filepath);

    // list files
    List<Filepath> extract_files(const Directory& directory);
    List<Filepath> extract_files_recursive(const Directory& directory);
    List<Directory> extract_directories(const Directory& directory);

    // query directory
    Filepath find_in_directory(const Filename& filename, const Directory& directory);
}