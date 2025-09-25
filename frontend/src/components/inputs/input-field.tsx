import { ChangeEvent, useEffect, useState } from "react";
import { InputFieldProps } from "../../../types/input-types";
import {
  FormControl,
  FormField,
  FormItem,
  FormLabel,
  FormMessage,
} from "../ui/form";
import { Input } from "../ui/input";

export function InputField({
  label,
  unit,
  name,
  placeholder = "enter value...",
  isReadOnly = false,
  control,
}: InputFieldProps) {
  return (
    <FormField
      control={control}
      name={name}
      render={({ field }) => (
        <FormItem className="w-full">
          <FormLabel>{label}</FormLabel>
          <FormControl>
            <div className="flex items-center gap-2">
              <Input
                placeholder={placeholder}
                type="number"
                step="any"
                readOnly={isReadOnly}
                className={`flex-1 ${
                  isReadOnly ? "bg-blue-50 border-blue-200" : ""
                }`}
                value={field.value === 0 ? "0" : field.value?.toString() ?? ""}
                onChange={(e) => {
                  const inputValue = e.target.value;

                  if (inputValue === "") {
                    // Treat empty as 0
                    field.onChange(0);
                  } else {
                    const numericValue = Number(inputValue);
                    if (!isNaN(numericValue)) {
                      field.onChange(numericValue);
                    }
                  }
                }}
                onBlur={field.onBlur}
                name={field.name}
              />
              {unit && (
                <span className="text-sm text-gray-600 min-w-fit whitespace-nowrap">
                  {unit}
                </span>
              )}
            </div>
          </FormControl>
          <FormMessage />
        </FormItem>
      )}
    />
  );
}
