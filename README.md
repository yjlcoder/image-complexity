## Image Complexity

This script will calculate the image complexity of every frame from a given video.

The script depends on OpenCV and some FFmpeg libraries (such as libavcodec-dev).

The way of calculating the image complexity is from [PHOG-Derived Aesthetic Measures Applied to Color Photographs of Artworks, Natural Scenes and Objects](https://www.researchgate.net/publication/259620648_PHOG-Derived_Aesthetic_Measures_Applied_to_Color_Photographs_of_Artworks_Natural_Scenes_and_Objects) by Redies et al.

### Install

```bash
git clone https://github.com/yang-jace-liu/image-complexity
cd image-complexity
./build.sh
```

You may encounter some problems while linking OpenCV.
Most of the problems can be solved by installing corresponding missing libraries:
For example that your OS not having libavcodec, you can install it by using `sudo apt install libavcodec-dev`.

### Usage

```bash
Usage: ./build/image-complexity <video path> <output path>
```

### Analyze

```bash
$ ./analyze.py -h
usage: analyze.py [-h] [--html-format] [--output-cdf OUTPUT_CDF] input

This script is to analyze the output of the image complexity extracting program.

positional arguments:
  input                 The input file

optional arguments:
  -h, --help            show this help message and exit
  --html-format         Generate html format output for the convenience of copying/pasting to Excel/Google Sheet/Apple Numbers.
  --output-cdf OUTPUT_CDF
                        a file path shows the CDF of the data. PDF format is preferred.
```

### Copy the analysis result to Excel / Google Sheets / Apple Numbers

For linux users:

```bash
$ ./analyze.py raw.txt --html-format | xclip -t text/html -selection clipboard
```

### TODOs

- Multithreading support