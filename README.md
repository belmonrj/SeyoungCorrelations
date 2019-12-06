# Seyoung Correlations

This README file is in progress...

## Macros

File name | description
--------- | -----------
DataTextFiles/barely.C | takes correlation text files and prints certain ratios to screen
mib.C | code from Seyoung/ShinIchi
newplot_pAu.C | makes the plot with the wide pT bins and peripheral subtraction
newplot_pAu_morebins.C | makes the plot with the narrow pT bins and peripheral subtraction
newplot_pAu_pp.C | makes the plot with the wide pT bins and pp subtraction
ratiod.C | compares the extracted v2 across the different subsystem combination types

## Data files

File name | description
--------- | -----------
new_data.txt | used by newplot_pAu.C
new_data_morebins.txt | used by newplot_pAu_morebins.C
new_data_pAu.txt | identical to new_data.txt
new_data_pAu_pp.txt | data file
new_data_pp.txt | used by newplot_pAu_pp.C
temp.txt | temp storage for some data
hdata_pAu_pAulm.root | produced by newplot_pAu.C
hdata_pAu_pAulm_morebins.root | produced by newplot_pAu_morebins.C
hdata_pAu_pplm.root | produced by newplot_pAu_pp.C

## Histogram management files

File name | description
--------- | -----------
HistogramFiles/gather_dAu.C | takes the large number of different correlation histogram files and merges them into a single file (dAu)
HistogramFiles/gather_pAu.C | takes the large number of different correlation histogram files and merges them into a single file (pAu)
HistogramFiles/gather_pAu_morebins.C | takes the large number of different correlation histogram files and merges them into a single file (pAu with more pT bins)
HistogramFiles/gather_pp.C | takes the large number of different correlation histogram files and merges them into a single file (pp)
HistogramFiles/seyoung_data.root | all histograms for pAu
HistogramFiles/seyoung_data_dau.root | all histograms for dAu
HistogramFiles/seyoung_data_morebins.root | all histograms for pT with more pT bins
HistogramFiles/seyoung_data_pp.root | all histograms for pp

