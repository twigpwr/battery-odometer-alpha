'''
Created on May 16, 2022

@author: Khai
'''
import os
import csv
import configparser
import subprocess

# Install module
cmd_xlsxwriter = "py -m pip install XlsxWriter"
os.system(cmd_xlsxwriter)
cmd_workbook = "py -m pip install Workbook"
os.system(cmd_workbook)

from xlsxwriter.workbook import Workbook
# importing python modules


hycon_ElfInput_File = r''
hycon_A2lInput_File =r''
hycon_CsvMapping_File = r''
hycon_A2lOutput_File = r''


hycon_Csv_Converted = r'temp.xlsx'
hycon_A2L_Modified = r'a2lModified.a2l'
hycon_A2L_Updated = r'a2lUpdated.a2l'


def Hycon_Covert_Csv2Xlsx():
    global hycon_CsvMapping_File
    
    workbook = Workbook(hycon_Csv_Converted)
    worksheet = workbook.add_worksheet()

    with open(hycon_CsvMapping_File, 'r', encoding='utf8') as f:
    # with open(hycon_CsvMapping_File, 'r') as f:
        reader = csv.reader(f)
        for r, row in enumerate(reader):
            for c, col in enumerate(row):
                worksheet.write(r, c, col)
    workbook.close()

def Hycon_Get_Path():
    global hycon_CsvMapping_File
    global hycon_ElfInput_File
    global hycon_A2lInput_File
    global hycon_A2lOutput_File
    
    config = configparser.ConfigParser()
    config.optionxform = str
    config.read('CONFIG.INI')
    hycon_ElfInput_File = config['INPUT']['INPUT_ELF']
    hycon_CsvMapping_File = config['MAPPING']['MAPPING_CSV_FILE']
    hycon_A2lInput_File = config['INPUT']['INPUT_APPLICATION_A2L']
    hycon_A2lOutput_File = config['OUTPUT']['OUTPUT_KW38_A2L']

if __name__ == '__main__':

    os.system("rm -f " + hycon_Csv_Converted)
    os.system("rm -f " + hycon_A2L_Modified)
    os.system("rm -f " + hycon_A2L_Updated)
    Hycon_Get_Path()
    Hycon_Covert_Csv2Xlsx()
    cmd_modify = r'ASAP2Modifier.exe -A ' + hycon_A2lInput_File + r' -I ASAP2_Setting/Modifier.INI -L log.txt -O ' + hycon_A2L_Modified + r' -X ' + hycon_Csv_Converted
    os.system(cmd_modify)
    subprocess.run(cmd_modify, shell=True)

    
    cmd_update = r"ASAP2Updater -I " + hycon_A2L_Modified + r" -A " + hycon_ElfInput_File + r" -O " + hycon_A2L_Updated + r" -L log.txt -T ASAP2_Setting/Updater.INI"
    os.system(cmd_update)
    subprocess.run(cmd_update, shell=True)
    
    cmd_merge = r"ASAP2Merger -M " + hycon_A2lOutput_File + r" -O " + hycon_A2lOutput_File + r" -S " + hycon_A2L_Updated + r" -P ASAP2_Setting/Merger.INI -L log.txt"
    os.system(cmd_merge)
    subprocess.run(cmd_merge, shell=True)

    os.system("rm -f " + hycon_Csv_Converted)
    os.system("rm -f " + hycon_A2L_Modified)
    os.system("rm -f " + hycon_A2L_Updated)
    