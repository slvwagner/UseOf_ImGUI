#include "Header.h"

using namespace cv;

/// <summary>
/// Simple helper function to load an image into a OpenGL texture with common settings
/// </summary>
/// <param name="filename"></param>
/// <param name="out_texture"></param>
/// <param name="out_width"></param>
/// <param name="out_height"></param>
/// <returns></returns>
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}


/// <summary>
/// Get the actrual working directory as a character string
/// </summary>
/// <returns>string</returns>
string getwd()
{
    // find working directory
    char* cwd = _getcwd(NULL, 0);
    if (cwd == NULL)
    {
        return "error in _getcwd";
    }
    string cfilePath(cwd);
    free(cwd);
    replace(cfilePath.begin(), cfilePath.end(), '\\', '/');

    return cfilePath + "/";
}

/// <summary>
/// Read image file
/// </summary>
/// <param name="filePathName"></param>
/// <returns>cv::Mat (Image)</returns>
Mat GetImage(string filePathName)
{
    Mat image = imread(filePathName);
    if (image.empty()) return image;
    else
    {
        cout << "Could not read file: " << filePathName << endl;
        return Mat();
    }
}


/// <summary>
/// Write CV Matrix to an xml file 
/// </summary>
/// <param name="cv::Mat (Matrix)"></param>
/// <param name="string (filename)"></param>
void writeMatToFile(cv::Mat& matrix, const char* filename)
{
    ofstream fout(filename);
    if (!fout)
    {
        cout << "File Not Opened" << endl;  return;
    }
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            fout << matrix.at<float>(i, j) << ";";
        }
        fout << endl;
    }
    fout.close();
}

/// <summary>
/// find all files in specific directory 
/// </summary>
/// <param name="dir_name"></param>
/// <param name="extension"></param>
/// <returns></returns>
vector<string> list_files_by_extension(const string& dir_name, const string& extension)
{
    // return vector
    vector<string> files;

    // Convert the narrow character directory name and extension to wide character strings
    wstring wdir_name(dir_name.begin(), dir_name.end());
    wstring wextension(extension.begin(), extension.end());

    // Concatenate the search pattern and the directory name
    wchar_t search_pattern[MAX_PATH];
    swprintf(search_pattern, L"%ls\\*%ls", wdir_name.c_str(), wextension.c_str());

    // Find the first file in the directory
    WIN32_FIND_DATAW find_data;
    HANDLE find_handle = FindFirstFileW(search_pattern, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE)
    {
        return files;
    }

    // Add the names of the files with the specified extension to the vector
    do
    {
        if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            // Convert the wide character file name to a narrow character string
            char file_name[MAX_PATH];
            wcstombs(file_name, find_data.cFileName, MAX_PATH);
            files.push_back(file_name);
        }
    } while (FindNextFileW(find_handle, &find_data));

    // Close the search handle
    FindClose(find_handle);

    return files;
}


/// <summary>
/// find all files with specifix file extention in directrory
/// </summary>
/// <param name="dir_name"></param>
/// <param name="pattern"></param>
/// <returns></returns>
vector<string> list_files_by_pattern(const string& dir_name, const string& pattern)
{
    vector<string> files;

    // Convert the narrow character directory name and pattern to wide character strings
    wstring wdir_name(dir_name.begin(), dir_name.end());
    wstring wpattern(pattern.begin(), pattern.end());

    // Concatenate the search pattern and the directory name
    wchar_t search_pattern[MAX_PATH];
    swprintf(search_pattern, L"%ls\\*%ls*", wdir_name.c_str(), wpattern.c_str());

    // Find the first file in the directory
    WIN32_FIND_DATAW find_data;
    HANDLE find_handle = FindFirstFileW(search_pattern, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE)
    {
        return files;
    }

    // Add the names of the files that contain the pattern to the vector
    do
    {
        if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            // Convert the wide character file name to a narrow character string
            char file_name[MAX_PATH];
            wcstombs(file_name, find_data.cFileName, MAX_PATH);
            files.push_back(file_name);
        }
    } while (FindNextFileW(find_handle, &find_data));

    // Close the search handle
    FindClose(find_handle);

    return files;
}


/// <summary>
/// Convert a "int" to a string
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
char* int_to_string(int value)
{
    // Allocate a buffer large enough to hold the maximum number of digits
    // plus the null terminator
    char* buffer = (char*)malloc(sizeof(char) * 32);

    // Convert the integer to a string using snprintf
    snprintf(buffer, 32, "%d", value);

    // Return the string
    return buffer;
}

/// <summary>
/// Convert a "double" to a string
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
char* double_to_string(double value)
{
    // Allocate a buffer large enough to hold the maximum number of digits
    // plus the null terminator
    char* buffer = (char*)malloc(sizeof(char) * 32);

    // Convert the double to a string using snprintf
    snprintf(buffer, 32, "%f", value);

    // Return the string
    return buffer;
}

/// <summary>
/// load all images from a directory and retruns an cv:Mat image vector
/// </summary>
/// <param name="imageFilePath"></param>
/// <param name="fileNames"></param>
/// <returns>Image vector</returns>
vector <cv::Mat> load_images(string imageFilePath, vector <string> fileNames)
{
    string cfile;
    vector <cv::Mat> images;
cv::Mat image;

    // load all files used for calib
    for (int ii = 0; ii < fileNames.size(); ii++)
    {
        cfile.clear();
        cfile = imageFilePath + fileNames[ii];
        image = cv::imread(cfile, cv::IMREAD_GRAYSCALE);
        if (!image.empty())
        {
            images.push_back(image);
        }
        else
        {
            break;
        }
    }
    return images;
}

/////////////////////////////

vector<cv::Point> points;

/// <summary>
/// on Mouse left click event
/// </summary>
/// <param name="event"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="flags"></param>
/// <param name="userdata"></param>
void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        points.push_back(cv::Point(x, y));
        cout << "Mouse position: (" << x << ", " << y << ")" << endl;
    }
}


/// <summary>
/// changing Constrast 
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onContrastTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_CONTRAST, pow(10.0, value / 100.0));
}

/// <summary>
/// Changing Brightness
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onBrightnessTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_BRIGHTNESS, pow(10.0, value / 100.0));
}

/// <summary>
/// Exposure
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onExposureTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_EXPOSURE, pow(10.0, value / 100.0));
}

/// <summary>
/// Saturation of color
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onSaturationTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_SATURATION, pow(10.0, value / 100.0));
}

/// <summary>
/// Changing gain
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onGainTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_GAIN, pow(10.0, value / 100.0));
}

/// <summary>
///  Chaning Gamma 
/// </summary>
/// <param name="value"></param>
/// <param name="userData"></param>
void onGammaTrackbarChange(int value, void* userData)
{
    cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(userData);
    capture->set(cv::CAP_PROP_GAMMA, pow(10.0, value / 100.0));
}