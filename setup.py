from setuptools import setup, find_packages

#here = path.abspath(path.dirname(__file__))
#long_description = ""
#with open("./README.md", encoding = 'utf-8') as f:
with open("README.md", "r") as fh:
    long_description = fh.read()


setup(
        name = "patchtool",
        version = 'v1.0-beta',
        description = """Line number chars terminator -- update past patches with its current line number""",
        url = 'https://github.com/HsimWong/patchtool/',
        author = "Xin WANG",
        author_email = 'hsimwong1202@gmail.com',
        long_description=long_description,
        long_description_content_type="text/markdown",
        classifiers = [
            'Development Status :: 3 - Alpha',
            'Intended Audience :: Developers',
            "License :: OSI Approved :: MIT License",
            'Programming Language :: Python :: 3',



            ],
        python_requires = ">=3.5",
        entry_points = {
            'console_scripts': [
                'patchtool=src.patchtool:main',
                ],
            }

        )
