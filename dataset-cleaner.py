import pandas as pd

def rebuild_dataset(dataset_dir):
    # Load the dataset
    dataset = pd.read_csv(dataset_dir)
    df = pd.DataFrame()

    timestamps = list(set(dataset['SampleTime']))

    df['Timestamp'] = timestamps

    sensors_numbers = list(set(dataset['SensorID']))

    sensors = ['sensor_' + str(sensor_number) for sensor_number in sensors_numbers]

    values = []
    for t in timestamps:
        values.append(list(dataset[dataset['SampleTime'] == t]['Value']))

    df[sensors] = values

    df.to_csv('dataset/dataset_clean.csv', index=False)

    return df


def split_dataset(df):
    # Split the dataframe in 40 parts contiguously
    parts = 40
    df_parts = [df[i*int(len(df)/parts):(i+1)*int(len(df)/parts)] for i in range(parts)]

    for i in range(parts):
        df_parts[i].to_csv('dataset/dataset_clean_part' + str(i) + '.csv', index=False) 


if __name__ == '__main__':
    dataset_dir = 'dataset/data857489168.csv'
    
    df = rebuild_dataset(dataset_dir)
    split_dataset(df)
