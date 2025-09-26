"use client";

import { InputField } from "./input-field";
import { InputDropdown } from "./input-dropdown";
import { InputUpload } from "./input-upload";
import { Control } from "react-hook-form";
import { InputWidgetProps } from "../../../types/input-types";

export function InputWidget({
  inputType,
  control,
  onFileLoad,
}: InputWidgetProps) {
  const handleFileLoad = (filePath: string, data: number[][]) => {
    onFileLoad?.(inputType.name, data);
  };

  switch (inputType.type) {
    case "field":
      return (
        <InputField
          label={inputType.label}
          unit={inputType.unit}
          name={inputType.name}
          placeholder={inputType.placeholder}
          isReadOnly={inputType.isReadOnly}
          control={control}
        />
      );

    case "dropdown":
      return (
        <InputDropdown
          label={inputType.label}
          name={inputType.name}
          options={inputType.options || []}
          control={control}
        />
      );

    case "upload":
      return (
        <InputUpload
          label={inputType.label}
          name={inputType.name}
          requiredColumns={inputType.requiredColumns}
          control={control}
          onFileLoad={handleFileLoad}
        />
      );

    case "field-upload":
      return (
        <div className="flex flex-col gap-2">
          <InputField
            label={inputType.label}
            unit={inputType.unit}
            name={inputType.name}
            placeholder={inputType.placeholder}
            isReadOnly={inputType.isReadOnly}
            control={control}
          />
          <InputUpload
            name={inputType.name}
            requiredColumns={inputType.requiredColumns}
            control={control}
            onFileLoad={handleFileLoad}
          />
        </div>
      );

    default:
      return (
        <div className="w-full p-4 border border-red-300 rounded-lg bg-red-50">
          <p className="text-red-600 text-sm">
            Invalid input type: {inputType.type}
          </p>
        </div>
      );
  }
}
