import csv
import pandas as pd
import logging
from nameparser import HumanName

LOG_FILE = 'logs/log.txt'
# clean previous logs from log file
open(LOG_FILE, 'w').close()
logging.basicConfig(filename=LOG_FILE, level=logging.DEBUG)

class FileParser:
    """Parse the file following specified instructions."""

    def __init__(self, input_file, output_file, columns_to_split=None):
        self.input_file = input_file
        self.output_file = output_file


    def build(self):
        """Entry point for parsing the input file and generating
        parsed output.
        """
        df = self.get_dataframe()
        parsed_document = self.parsed_document(df)
        self.generate_output(parsed_document)


    def get_dataframe(self):
        """Use Pandas to read in file and return dataframe object."""
        return pd.read_csv(self.input_file, error_bad_lines=False)


    def parsed_document(self, df):
        """Splits raw_headline, raw_full_name columns.

        Args:
            df: pandas dataframe object

        Returns:
            The list of lists, representing each record, containing the
            original data, and the split information for raw_healine and
            raw_full_name columns.
        """
        final_output = []
        for index, row in df.iterrows():

            title, company_name = self.split_headline(row)
            first_name, last_name = self.split_full_name(row)
            final_output.append([
                row['id'], row['raw_full_name'], row['raw_headline'],
                title, first_name, last_name, company_name
            ])
        return final_output


    def split_headline(self, row):
        """Split Headline Column.

        Args:
            row: raw_headline column for a single record

        Returns:
            title: string representing position title
            column_name: string represting the name of the company
        """
        try:
            # handle rare occasions of '@' instead of 'at'
            if '@' in row['raw_headline']:
                splitted_headline = row['raw_headline'].split('@', 1)
            else:
                splitted_headline = row['raw_headline'].rsplit(' at ', 1)
            # check to see if the split event occured
            if len(splitted_headline) > 1:
                title, company_name = splitted_headline
            else:
                title = splitted_headline[0]
                company_name = 'n/a'
        except ValueError as e:
            logging.debug(
                """>>> title or company_name were missing or improperly parsed for raw_headline => {}
                {}""".format(e, row['raw_headline'])
            )
            title = 'n/a'
            company_name = 'n/a'
        return (title, company_name)


    def split_full_name(self, row):
        """Split Full Name Column.

        Args:
            row: raw_headline column for a single record

        Returns:
            first_name: string representing first name of an employee
            last_name: string represting last name of an employee
        """
        try:
            full_name = HumanName(row['raw_full_name'])
            first_name = full_name.first
            last_name = full_name.last
        except ValueError as e:
            logging.debug(
                """>>> first_name or last_name were missing or improperly properly for raw_full_name => {}
                {}""".format(e, row['raw_full_name'])
            )
            first_name = 'n/a'
            last_name = 'n/a'
        return (first_name, last_name)


    def generate_output(self, parsed_document):
        """Generate the out in the indicated output file.

        Args:
            parsed_document list: contains all parsed items to be added to the output.
        """
        with open(self.output_file, 'w', newline='') as out_f:
            writer = csv.writer(out_f)
            writer.writerow(['id', 'raw_full_name', 'raw_headline', 'title', 'first_name', 'last_name', 'company_name'])
            writer.writerows(parsed_document)
        print('>>>> Output has been generated in file: {}'.format(self.output_file))



if __name__ == '__main__':
    file_parser = FileParser(input_file='nwd-code-challenge/nwd-code-challenge-input.csv',
                             output_file='my-solution-2018-03-26.csv')
    file_parser.build()
