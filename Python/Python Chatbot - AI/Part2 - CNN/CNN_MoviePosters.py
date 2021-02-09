# Import modules
import pandas as pd
import numpy as np
import os
import tensorflow as tf
import cv2
import random
from tensorflow import keras
from tensorflow.keras import layers
from matplotlib import pyplot as plt
import matplotlib.image as mpimg

# Define batch size for CNN, then image dims and training folder
batchSize = 32
imgWidth = 200
imgHeight = 200
imgFolder = r'C:\Users\jordi\Desktop\cnn_train\1'

# Preprocess training dataset from directory
# Splits the dataset to utilises for validation
trainDS = tf.keras.preprocessing.image_dataset_from_directory(
    imgFolder,
    validation_split = 0.2,
    subset = "training",
    seed = 123,
    image_size = (imgHeight, imgWidth),
    batch_size = batchSize)

# Use the same dataset for validation
valDS = tf.keras.preprocessing.image_dataset_from_directory(
    imgFolder,
    validation_split = 0.2,
    subset = "validation",
    seed = 123,
    image_size = (imgHeight, imgWidth),
    batch_size = batchSize)

# Obtain class names from dataset
classNames = trainDS.class_names
print(classNames)

# Configure for performance
# Ensures the dataset does not become a bottleneck during training
AUTOTUNE = tf.data.experimental.AUTOTUNE

trainDS = trainDS.cache().shuffle(1000).prefetch(buffer_size = AUTOTUNE)
valDS = valDS.cache().prefetch(buffer_size = AUTOTUNE)


# Standardise dataset
normalizationLayer = layers.experimental.preprocessing.Rescaling(1./255)

normalizedDS = trainDS.map(lambda x, y: (normalizationLayer(x), y))
imageBatch, labelsBatch = next(iter(normalizedDS))
firstImage = imageBatch[0]
print(np.min(firstImage), np.max(firstImage))


# Augment the data to counteract overfitting
dataAug = keras.Sequential(
  [
    layers.experimental.preprocessing.RandomFlip("horizontal", 
                                                 input_shape = (imgHeight, 
                                                                imgWidth,
                                                                3)),
    layers.experimental.preprocessing.RandomRotation(0.1),
    layers.experimental.preprocessing.RandomZoom(0.1),
  ]
)


# Create model
model = tf.keras.Sequential([
    dataAug,
    layers.experimental.preprocessing.Rescaling(1./255),
    layers.Conv2D(16, 3, padding='same', activation='relu'),
    layers.MaxPooling2D(),
    layers.Conv2D(32, 3, padding='same', activation='relu'),
    layers.MaxPooling2D(),
    layers.Conv2D(64, 3, padding='same', activation='relu'),
    layers.MaxPooling2D(),
    layers.Flatten(),
    layers.Dense(256, activation='relu'),
    layers.Dense(len(classNames))
])


# Compile the model
model.compile(optimizer = 'adam',
              loss = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics = ['accuracy'])

# Print summary of model
model.summary()

# Define number of epochs
epochs = 30

# Train the model
history = model.fit(trainDS,
                    validation_data = valDS,
                    epochs = epochs)

# Show data for accuracy and loss via graphs
acc = history.history['accuracy']
valAcc = history.history['val_accuracy']

loss = history.history['loss']
valLoss = history.history['val_loss']

epochsRange = range(epochs)

plt.figure(figsize=(8, 8))
plt.subplot(1, 2, 1)
plt.plot(epochsRange, acc, label = 'Training Accuracy')
plt.plot(epochsRange, valAcc, label = 'Validation Accuracy')
plt.legend(loc = 'lower right')
plt.title('Training and Validation Accuracy')

plt.subplot(1, 2, 2)
plt.plot(epochsRange, loss, label = 'Training Loss')
plt.plot(epochsRange, valLoss, label = 'Validation Loss')
plt.legend(loc = 'upper right')
plt.title('Training and Validation Loss')
plt.show()


# Save the model
model.save('MoviePosterModel.h5')




