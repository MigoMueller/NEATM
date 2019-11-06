from setuptools import setup, find_packages


__version__ = '0.7'

setup(
    name='neatm',
    version=__version__,
    author='Migo Mueller',
    author_email='m.mueller@astro.rug.nl',
    install_requires=[
        'numpy',
        'astropy'
    ],
    license='LICENSE.txt',
    description='Tool to model asteroid thermal emission following the Near-Earth Asteroid Thermal Model (Harris 1998).',
    keywords = ['Asteroids', 'Thermal emission', 'NEATM', 'Planetary Science'],
    packages=['neatm'],
    classifiers = [
        "Programming Language :: Python :: 3.5",
        "Operating System :: OS Independent"
        "Intended Audience :: Science/Research/DataAnalysis",
        #"License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)",
        "Topic :: Scientific/Engineering"
    ],
    include_package_data=True
)
