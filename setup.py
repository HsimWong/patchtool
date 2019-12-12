from setuptools import setup, find_packages

with open("README.md", "r") as fh:
    long_description = fh.read()


setup(
    name="patchtool", # Replace with your own username
    version="1.2.0-0",
    author="Xin WANG",
    author_email="hsimwong1202@gmail.com",
    description="Converting patches of old version to the ones with current line number",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/HsimWong/patchtool",
    packages=find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Operating System :: OS Independent",
    ],
    entry_points = {
        'console_scripts':[
            'patchtool = patchtool.main:main'
        ]
    }
   
    

)


