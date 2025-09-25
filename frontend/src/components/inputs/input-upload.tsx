"use client";

import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import {
  FormControl,
  FormField,
  FormItem,
  FormLabel,
  FormMessage,
} from "@/components/ui/form";
import { useState, useRef } from "react";
import { Upload, File, AlertCircle } from "lucide-react";
import { toast } from "sonner";
import { Control } from "react-hook-form";
import { InputUploadProps } from "../../../types/input-types";

export function InputUpload({
  label,
  name,
  requiredColumns = 0,
  control,
  onFileLoad,
}: InputUploadProps) {
  const [fileName, setFileName] = useState<string>("No file selected");
  const [isLoaded, setIsLoaded] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const fileInputRef = useRef<HTMLInputElement>(null);

  const validateColumnCount = (row: string[]): boolean => {
    if (requiredColumns > 0 && row.length < requiredColumns) {
      return false;
    }
    return true;
  };

  const parseCsvData = (csvText: string): number[][] => {
    const lines = csvText.split("\n").filter((line) => line.trim() !== "");
    const data: number[][] = [];

    for (let i = 0; i < lines.length; i++) {
      const values = lines[i].split(",").map((val) => val.trim());

      if (!validateColumnCount(values)) {
        throw new Error(
          `Line ${
            i + 1
          } doesn't have enough columns (required: ${requiredColumns}, found: ${
            values.length
          })`
        );
      }

      const rowData: number[] = values.map((value) => {
        const numValue = parseFloat(value);
        return isNaN(numValue) ? 0.0 : numValue;
      });

      data.push(rowData);
    }

    return data;
  };

  const handleFileSelect = async (
    event: React.ChangeEvent<HTMLInputElement>,
    field: any
  ) => {
    const file = event.target.files?.[0];
    if (!file) {
      return;
    }

    if (!file.name.toLowerCase().endsWith(".csv")) {
      const errorMsg = "Please select a CSV file";
      setError(errorMsg);
      setFileName("Invalid file type");
      toast.error("Upload Error", { description: errorMsg });
      return;
    }

    try {
      const text = await file.text();
      const data = parseCsvData(text);

      if (data.length === 0) {
        throw new Error("File contains no valid data");
      }

      setFileName(file.name);
      setIsLoaded(true);
      setError(null);

      // Set form field value to file path/name
      field.onChange(file.name);

      // Call callback with parsed data
      onFileLoad?.(fileName, data);

      toast.success("File loaded successfully", {
        description: `${data.length} rows loaded from ${file.name}`,
      });
    } catch (err) {
      const errorMsg =
        err instanceof Error ? err.message : "Failed to read CSV file";
      setError(errorMsg);
      setFileName("Failed to load file");
      setIsLoaded(false);
      field.onChange("");
      toast.error("Upload Error", { description: errorMsg });
    }
  };

  return (
    <FormField
      control={control}
      name={name}
      render={({ field }) => (
        <FormItem className="w-full">
          <FormLabel>{label}</FormLabel>
          <FormControl>
            <div className="flex items-center gap-3">
              <Button
                type="button"
                variant="outline"
                size="sm"
                onClick={() => fileInputRef.current?.click()}
                className="flex items-center gap-2"
              >
                <Upload size={16} />
                Choose CSV File
              </Button>

              <div className="flex items-center gap-2 flex-1">
                {isLoaded ? (
                  <File size={16} className="text-green-600" />
                ) : error ? (
                  <AlertCircle size={16} className="text-red-600" />
                ) : (
                  <File size={16} className="text-gray-400" />
                )}

                <span
                  className={`text-sm ${
                    isLoaded
                      ? "text-gray-700"
                      : error
                      ? "text-red-600"
                      : "text-gray-500"
                  }`}
                >
                  {fileName}
                </span>
              </div>

              <Input
                ref={fileInputRef}
                type="file"
                accept=".csv"
                className="hidden"
                onChange={(e) => handleFileSelect(e, field)}
              />
            </div>
          </FormControl>
          <FormMessage />
        </FormItem>
      )}
    />
  );
}
