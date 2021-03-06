/*=========================================================================
 *
 *  Copyright David Doria 2012 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "PoissonEditing.h"
#include "PoissonEditingWrappers.h"

// Submodules
#include "Mask/ITKHelpers/ITKHelpers.h"

// STL
#include <iostream>

// ITK
#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkCovariantVector.h"

static void TestVectorImage();
static void TestCovariantVectorImage();
static void TestScalarImage();

int main(int, char* [])
{
  TestVectorImage();
  TestCovariantVectorImage();
  TestScalarImage();

  return EXIT_SUCCESS;
}

void TestVectorImage()
{
  typedef float ComponentType;

  typedef itk::VectorImage<ComponentType, 2> ImageType;

  ImageType::Pointer image = ImageType::New();
  ImageType::Pointer output = ImageType::New();

  Mask::Pointer mask = Mask::New();

  typedef PoissonEditing<ComponentType> PoissonEditingType;

  PoissonEditingType::GuidanceFieldType::Pointer guidanceField =
          PoissonEditingType::GuidanceFieldType::New();

  std::vector<PoissonEditingType::GuidanceFieldType::Pointer> guidanceFields(
         image->GetNumberOfComponentsPerPixel(), guidanceField);

  itk::ImageRegion<2> regionToProcess = image->GetLargestPossibleRegion();

  FillImage(image.GetPointer(), mask.GetPointer(),
            guidanceFields, output.GetPointer(), regionToProcess);

  FillImage(image.GetPointer(), mask.GetPointer(),
            guidanceField.GetPointer(), output.GetPointer(), regionToProcess);
}

void TestScalarImage()
{
  typedef float ComponentType;

  typedef itk::Image<ComponentType, 2> ImageType;

  ImageType::Pointer image = ImageType::New();
  ImageType::Pointer output = ImageType::New();

  Mask::Pointer mask = Mask::New();

  typedef PoissonEditing<ComponentType> PoissonEditingType;

  PoissonEditingType::GuidanceFieldType::Pointer guidanceField =
      PoissonEditingType::GuidanceFieldType::New();

  itk::ImageRegion<2> regionToProcess = image->GetLargestPossibleRegion();

  FillImage(image.GetPointer(), mask,
            guidanceField.GetPointer(), output.GetPointer(), regionToProcess);
}

void TestCovariantVectorImage()
{
  typedef float ComponentType;

  typedef itk::Image<itk::CovariantVector<ComponentType, 3>, 2> ImageType;

  ImageType::Pointer image = ImageType::New();
  ImageType::Pointer output = ImageType::New();

  Mask::Pointer mask = Mask::New();

  typedef PoissonEditing<ComponentType> PoissonEditingType;

  PoissonEditingType::GuidanceFieldType::Pointer guidanceField = PoissonEditingType::GuidanceFieldType::New();

  std::vector<PoissonEditingType::GuidanceFieldType::Pointer> guidanceFields(
         image->GetNumberOfComponentsPerPixel(), guidanceField);

  itk::ImageRegion<2> regionToProcess = image->GetLargestPossibleRegion();

  FillImage(image.GetPointer(), mask,
            guidanceFields, output.GetPointer(), regionToProcess);

  FillImage(image.GetPointer(), mask.GetPointer(),
            guidanceField.GetPointer(), output.GetPointer(), regionToProcess);

}
